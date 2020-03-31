// 作成者 : 板場
#include "WavefrontOBJ_loader.hpp"

BEGIN_EGEG

// WavefrontOBJLoader 関数定義
/*===========================================================================*/
// コンストラクタ
WavefrontOBJLoader::WavefrontOBJLoader() 
{
    initialize();
}

// 初期化
void WavefrontOBJLoader::initialize()
{
    // 読み込み関数をセット
    //  キー はコマンド
    //  要素 はコマンドに対応した関数のアドレス
    load_function_list_.emplace( "v", &WavefrontOBJLoader::loadVertexPosition );
    load_function_list_.emplace( "vt", &WavefrontOBJLoader::loadVertexUV );
    load_function_list_.emplace( "vn", &WavefrontOBJLoader::loadVertexNormal );
    load_function_list_.emplace( "f", &WavefrontOBJLoader::loadFace );
    load_function_list_.emplace( "g", &WavefrontOBJLoader::loadGroupName );
    load_function_list_.emplace( "mtllib", &WavefrontOBJLoader::loadMaterialFile );
    load_function_list_.emplace( "usemtl", &WavefrontOBJLoader::loadUseMaterialName );
    load_function_list_.emplace( "newmtl", &WavefrontOBJLoader::loadMaterialName );
    load_function_list_.emplace( "Kd", &WavefrontOBJLoader::loadMaterialDiffuseColor );
    load_function_list_.emplace( "Ks", &WavefrontOBJLoader::loadMaterialSpecularColor );
    load_function_list_.emplace( "Ka", &WavefrontOBJLoader::loadMaterialAmbientColor );
    load_function_list_.emplace( "d", &WavefrontOBJLoader::loadMaterialTransparency );
    load_function_list_.emplace( "Ni", &WavefrontOBJLoader::loadMaterialRefractiveIndex );
}

// ファイル読み込む
DetailedReturnValue<bool> WavefrontOBJLoader::load( const std::string& FileName, Mesh* Output )
{
    using RetTy = DetailedReturnValue<bool>;

    // ファイルオープン
    std::fstream stream( FileName );
    if( !stream )
    { // 失敗
        return RetTy( false, "ファイルオープンに失敗" );
    }

    // 前回読み込み時のデータをクリア
    //  std::vector::clear()の計算量は線形時間。前回のデータをクリアした方が速度的に無駄が無い。
    temp_output_.position.clear();
    temp_output_.uv.clear();
    temp_output_.normal.clear();
    temp_output_.position_for_buffer.clear();
    temp_output_.uv_for_buffer.clear();
    temp_output_.normal_for_buffer.clear();
    temp_output_.index_for_buffer.clear();
    temp_output_.curr_vertex_index = 0U;
    temp_output_.group_list.clear();
    temp_output_.material_list.clear();

    // ファイル読み込み
    std::string command;
    while( stream >> command )
    { // ファイル終端まで読み込む
        auto func_itr = load_function_list_.find( command.c_str() );
        if( func_itr != load_function_list_.end() )
        { // 対応するコマンドの場合、処理を行う
            (this->*func_itr->second)(stream);
        }
    }
    stream.close();

    // バッファオブジェクトの生成
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    // 出力用データの作成
    using namespace Microsoft::WRL;
    ComPtr<ID3D11Buffer> position_buffer;
    ComPtr<ID3D11Buffer> uv_buffer;
    ComPtr<ID3D11Buffer> normal_buffer;
    ComPtr<ID3D11Buffer> index_buffer;
    if( !engine_->createBuffer(&desc, temp_output_.position_for_buffer, &position_buffer) )
    { // 失敗
        return RetTy( false, "座標用頂点バッファの作成に失敗" );
    }
    if( !engine_->createBuffer(&desc, temp_output_.uv_for_buffer, &uv_buffer) )
    { // 失敗
        return RetTy( false, "UV座標用頂点バッファの作成に失敗" );
    }
    if( !engine_->createBuffer(&desc, temp_output_.normal_for_buffer, &normal_buffer) )
    { // 失敗
        return RetTy( false, "法線ベクトル用頂点バッファの作成に失敗" );
    }
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    if( !engine_->createBuffer(&desc, temp_output_.index_for_buffer, &index_buffer ) )
    { // 失敗
        return RetTy( false, "インデックスバッファの作成に失敗" );
    }

    // 頂点データをセット
    Output->vertices.set<Tag_VertexPosition>( position_buffer );
    Output->vertices.set<Tag_VertexUV>( uv_buffer );
    Output->vertices.set<Tag_VertexNormal>( normal_buffer );
    Output->vertices.set<Tag_VertexIndex>( index_buffer );
    // サブメッシュをセット
    SubMesh submesh;
    for( auto group : temp_output_.group_list )
    { // グループからサブメッシュをコピー
        auto mtl_itr = temp_output_.material_list.find(group.second.material_name);
        if( mtl_itr != temp_output_.material_list.end() )
            submesh.material = std::move( mtl_itr->second );
        submesh.start_index = group.second.start_index; 
        submesh.num_vertices = group.second.num_vertices;

        Output->submesh_list.push_back( submesh );
    }

    return true;
}

// 頂点座標の読み込み
void WavefrontOBJLoader::loadVertexPosition( std::fstream& Stream )
{
    temp_output_.position.emplace_back();
    auto& pos = temp_output_.position.back();
    Stream >>
        pos.x >>
        pos.y >>
        pos.z;
}

// 頂点UV座標の読み込み
void WavefrontOBJLoader::loadVertexUV( std::fstream& Stream )
{
    temp_output_.uv.emplace_back();
    auto& uv = temp_output_.uv.back();
    Stream >>
        uv.x >>
        uv.y;
}

// 頂点法線ベクトルの読み込み
void WavefrontOBJLoader::loadVertexNormal( std::fstream& Stream )
{
    temp_output_.normal.emplace_back();
    auto& normal = temp_output_.normal.back();
    Stream >>
        normal.x >>
        normal.y >>
        normal.z;
}

// 面の読み込み
void WavefrontOBJLoader::loadFace( std::fstream& Stream )
{
    // 面が所属するグループ
    auto group_itr = temp_output_.group_list.find(temp_output_.curr_group_name);
    if( group_itr == temp_output_.group_list.end() )
    { // 新規グループの場合、リストにグループを追加
        // Attention : マテリアルは一時出力からコピーしている。
        //             ムーブの方が高速だが、ムーブによる不具合を現時点で予想できない。
        Group g;
        g.material_name = temp_output_.curr_material_name;
        g.start_index = temp_output_.curr_vertex_index;
        g.num_vertices = 0U;
        temp_output_.group_list.emplace(temp_output_.curr_group_name, std::move(g));
       
        group_itr = temp_output_.group_list.find(temp_output_.curr_group_name);
    }

    // 面の追加( インデックス )
    temp_output_.index_for_buffer.push_back( temp_output_.curr_vertex_index + 2U );
    temp_output_.index_for_buffer.push_back( temp_output_.curr_vertex_index + 1U );
    temp_output_.index_for_buffer.push_back( temp_output_.curr_vertex_index );
    temp_output_.curr_vertex_index += 3U;
    group_itr->second.num_vertices += 3U;

    // 面の追加( 頂点 )
    std::string data;
    int pos_idx;
    int uv_idx;
    int nml_idx;
    for( int i = 0; i < 3; ++i )
    { // 面を形成する頂点を読み込む : 3頂点分
        Stream >> data;
        sscanf_s( data.c_str(),
            "%d/%d/%d",
            &pos_idx,
            &uv_idx,
            &nml_idx
        );

        temp_output_.position_for_buffer.push_back( temp_output_.position.at(pos_idx - 1U) );
        temp_output_.uv_for_buffer.push_back( temp_output_.uv.at(uv_idx - 1U) );
        temp_output_.normal_for_buffer.push_back( temp_output_.normal.at(nml_idx - 1U) );
    }
}

// グループ名読み込み
void WavefrontOBJLoader::loadGroupName( std::fstream& Stream )
{
    Stream >> temp_output_.curr_group_name;
}

// 使用マテリアル名読み込み
void WavefrontOBJLoader::loadUseMaterialName( std::fstream& Stream )
{
    auto curr_group_itr = temp_output_.group_list.find( temp_output_.curr_group_name );
    if( curr_group_itr != temp_output_.group_list.end() )
    { // グループに使用するマテリアル名を設定
        Stream >> curr_group_itr->second.material_name;
    }
}

// マテリアルファイルの読み込み
void WavefrontOBJLoader::loadMaterialFile( std::fstream& Stream )
{
    std::string filename;
    Stream >> filename;

    // ファイルオープン
    std::fstream stream( filename );
    if( !stream ) return;

    // ファイル読み込み
    std::string command;
    while( stream >> command )
    { // ファイル終端まで読み込む
        auto func_itr = load_function_list_.find( command.c_str() );
        if( func_itr != load_function_list_.end() )
        { // 対応するコマンドの場合、処理を行う
            (this->*func_itr->second)(stream);
        }
    }
    stream.close();
}

// マテリアル名の読み込み
void WavefrontOBJLoader::loadMaterialName( std::fstream& Stream )
{
    Stream >> temp_output_.loading_material_name;
}

// マテリアル　拡散色の読み込み
void WavefrontOBJLoader::loadMaterialDiffuseColor( std::fstream& Stream )
{
    float diffuse;
    Stream >> diffuse;

    temp_output_.material_list[temp_output_.loading_material_name].set<
        Tag_MaterialDiffuseColor>( diffuse );
}

// マテリアル　鏡面色の読み込み
void WavefrontOBJLoader::loadMaterialSpecularColor( std::fstream& Stream )
{
    float specular;
    Stream >> specular;
    temp_output_.material_list[temp_output_.loading_material_name].set<
        Tag_MaterialSpecularColor>( specular );
}

// マテリアル　環境色の読み込み
void WavefrontOBJLoader::loadMaterialAmbientColor( std::fstream& Stream )
{
    float ambient;
    Stream >> ambient;
    temp_output_.material_list[temp_output_.loading_material_name].set<
        Tag_MaterialAmbientColor>( ambient );
}

// マテリアル　透明度の読み込み
void WavefrontOBJLoader::loadMaterialTransparency( std::fstream& Stream )
{
    float transparency;
    Stream >> transparency;
    temp_output_.material_list[temp_output_.loading_material_name].set<
        Tag_MaterialTransparency>( transparency );
}

// マテリアル　屈折率の読み込み
void WavefrontOBJLoader::loadMaterialRefractiveIndex( std::fstream& Stream )
{
    float ref_idx;
    Stream >> ref_idx;
    temp_output_.material_list[temp_output_.loading_material_name].set<
        Tag_MaterialRefractiveIndex>( ref_idx );
}


END_EGEG
// EOF
