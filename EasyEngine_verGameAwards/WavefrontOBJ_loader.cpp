// 作成者 : 板場
#include "WavefrontOBJ_loader.hpp"
#include "texture_loader.hpp"

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
    load_function_list_.emplace( "Kd", &WavefrontOBJLoader::loadMaterialColor<Tag_MaterialDiffuseColor> );
    load_function_list_.emplace( "Ks", &WavefrontOBJLoader::loadMaterialColor<Tag_MaterialSpecularColor> );
    load_function_list_.emplace( "Ka", &WavefrontOBJLoader::loadMaterialColor<Tag_MaterialAmbientColor> );
    load_function_list_.emplace( "d", &WavefrontOBJLoader::loadMaterialFloat<Tag_MaterialTransparency> );
    load_function_list_.emplace( "Ni", &WavefrontOBJLoader::loadMaterialFloat<Tag_MaterialRefractiveIndex> );
    load_function_list_.emplace( "map_Kd", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialDiffuseTexture> );
    load_function_list_.emplace( "map_Ks", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialSpecularTexture> );
    load_function_list_.emplace( "map_Ka", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialAmbientTexture> );
    load_function_list_.emplace( "map_Bump", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialBumpTexture> );
    load_function_list_.emplace( "map_D", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialTransparencyTexture> );
    load_function_list_.emplace( "refl", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialreflectionTexture> );
}

// ファイル読み込む
DetailedResult<bool> WavefrontOBJLoader::load( const std::string& FileName, Mesh* Output, const CoordinateSystem CoorSys )
{
    using RetTy = DetailedResult<bool>;

    // ファイルオープン
    std::fstream stream( FileName );
    if( !stream )
    { // 失敗
        return RetTy( Failure(), "ファイルオープンに失敗" );
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

    // 座標系の選択
    temp_output_.coordinate_system = CoorSys;

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
        return RetTy( Failure(), "座標用頂点バッファの作成に失敗" );
    }
    if( !engine_->createBuffer(&desc, temp_output_.uv_for_buffer, &uv_buffer) )
    { // 失敗
        return RetTy( Failure(), "UV座標用頂点バッファの作成に失敗" );
    }
    if( !engine_->createBuffer(&desc, temp_output_.normal_for_buffer, &normal_buffer) )
    { // 失敗
        return RetTy( Failure(), "法線ベクトル用頂点バッファの作成に失敗" );
    }
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    if( !engine_->createBuffer(&desc, temp_output_.index_for_buffer, &index_buffer ) )
    { // 失敗
        return RetTy( Failure(), "インデックスバッファの作成に失敗" );
    }

    // 頂点データをセット
    Output->vertices.set<Tag_VertexPosition>( position_buffer );
    Output->vertices.set<Tag_VertexUV>( uv_buffer );
    Output->vertices.set<Tag_VertexNormal>( normal_buffer );
    Output->vertices.set<Tag_VertexIndex>( index_buffer );
    // サブメッシュをセット
    SubMesh submesh;
    for( auto& group : temp_output_.group_list )
    { // グループからサブメッシュをコピー
        auto mtl_itr = temp_output_.material_list.find(group.second.material_name);
        if( mtl_itr != temp_output_.material_list.end() )
            submesh.material = std::move( mtl_itr->second );
        submesh.start_index = group.second.start_index; 
        submesh.num_vertices = group.second.num_vertices;

        Output->submesh_list.push_back( submesh );
    }

    return Success();
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

    // 右手座標系のツールで作成されたモデルは変換する
    if( temp_output_.coordinate_system == CoordinateSystem::kRightHand )
    {
        pos.z *= -1.0F;
    }
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

END_EGEG
// EOF
