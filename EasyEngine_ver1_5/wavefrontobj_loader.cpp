// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "wavefrontobj_loader.hpp"
#include "rendering_manager.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    const std::unordered_map<std::string, void(WavefrontobjLoader::*)(std::istream&)> kLoadFunctions
    {
        {"v", &WavefrontobjLoader::loadVertexPosition},
        {"vt", &WavefrontobjLoader::loadVertexUV},
        {"vn", &WavefrontobjLoader::loadVertexNormal},
        {"f", &WavefrontobjLoader::loadFace},
        {"g", &WavefrontobjLoader::loadGroupName},
        {"mtllib", &WavefrontobjLoader::loadMaterialFile},
        {"usemtl", &WavefrontobjLoader::loadUseMaterialName},
        {"newmtl", &WavefrontobjLoader::loadMaterialName},
        {"Kd", &WavefrontobjLoader::loadMaterialColor<TagMaterialDiffuseColor>},
        {"Ks", &WavefrontobjLoader::loadMaterialColor<TagMaterialSpecularColor>},
        {"Ka", &WavefrontobjLoader::loadMaterialColor<TagMaterialAmbientColor>},
        {"d", &WavefrontobjLoader::loadMaterialFloat<TagMaterialTransparency>},
        {"Ni", &WavefrontobjLoader::loadMaterialFloat<TagMaterialRefractiveIndex>},
        {"map_Kd", &WavefrontobjLoader::loadMaterialTexture<TagMaterialDiffuseTexture>},
        {"map_Ks", &WavefrontobjLoader::loadMaterialTexture<TagMaterialSpecularTexture>},
        {"map_Ka", &WavefrontobjLoader::loadMaterialTexture<TagMaterialAmbientTexture>},
        {"map_Bump", &WavefrontobjLoader::loadMaterialTexture<TagMaterialBumpTexture>},
        {"map_D", &WavefrontobjLoader::loadMaterialTexture<TagMaterialTransparencyTexture>},
        {"refl", &WavefrontobjLoader::loadMaterialTexture<TagMaterialReflectionTexture>}
    };
}


/******************************************************************************

	declaration

******************************************************************************/
DetailedReturnValue<bool> createVertexBuffers(
    ID3D11Device*,
    const std::vector<VertexPositionType>&,
    const std::vector<VertexUVType>&,
    const std::vector<VertexNormalType>&,
    const std::vector<uint32_t>&,
    ID3D11Buffer**, ID3D11Buffer**, ID3D11Buffer**, ID3D11Buffer** );


/******************************************************************************

	WavefrontobjLoader

******************************************************************************/
 // ファイル読み込み
DetailedReturnValue<bool> WavefrontobjLoader::load(
    const std::string& FilePath,
    CoordinateSystem   CoorSys,
    Mesh* MeshOut )
{
    using namespace Microsoft::WRL;

    std::fstream stream{ FilePath };
    if( !stream )
        return { Failure{}, "ファイルオープンに失敗しました。" };
    
    // 前回読み込み時のデータをクリア
    temp_output_ = TemporaryOutput{};

    temp_output_.coordinate_system = CoorSys;
    std::string command;
    while( stream >> command )
    {
        auto find_itr = kLoadFunctions.find( command );
        if( find_itr != kLoadFunctions.end() )
          // コマンドに対応した処理を呼び出す
            (this->*find_itr->second)( stream );
    }
    stream.close();

    // 頂点バッファの作成&
    ComPtr<ID3D11Buffer> pos_buf;
    ComPtr<ID3D11Buffer> uv_buf;
    ComPtr<ID3D11Buffer> norm_buf;
    ComPtr<ID3D11Buffer> idx_buf;
    auto res = createVertexBuffers( 
        getManager()->getD3DDevice().Get(),
        temp_output_.positions_buf,
        temp_output_.uvs_buf,
        temp_output_.normals_buf,
        temp_output_.index_buf,
        &pos_buf, &uv_buf, &norm_buf, &idx_buf );
    if( !res ) return { Failure{}, res.what() };
    MeshOut->vertices.set<TagVertexPosition>( pos_buf );
    MeshOut->vertices.set<TagVertexUV>( uv_buf );
    MeshOut->vertices.set<TagVertexNormal>( norm_buf );
    MeshOut->vertices.set<TagVertexIndex>( idx_buf );

    // サブメッシュの作成
    for( auto& group : temp_output_.groups )
    {
        SubMesh mesh{};
        
        auto mtl_itr = temp_output_.materials.find(group.second.material_name);
        if( mtl_itr != temp_output_.materials.end() )
        { // マテリアルをサブメッシュにコピー
            // Attention : 複数のグループが同一のマテリアルを保持する可能性があるのでムーブは使えない
            mesh.material = mtl_itr->second;
        }
        mesh.start_index  = group.second.start_index;
        mesh.num_vertices = group.second.num_vertices;

        MeshOut->sub_mesh_list.push_back( std::move(mesh) );
    }

    return Success{};
}


 // 頂点座標の読み込み
void WavefrontobjLoader::loadVertexPosition( std::istream& Stream )
{
    temp_output_.positions.emplace_back();
    auto& pos = temp_output_.positions.back();
    Stream >> pos.x >> pos.y >> pos.z;

    // 右手座標系のモデルは変換する
    if( temp_output_.coordinate_system == CoordinateSystem::kRightHand )
        pos.z *= -1.0F;
}


 // UV座標の読み込み
void WavefrontobjLoader::loadVertexUV( std::istream& Stream )
{
    temp_output_.uvs.emplace_back();
    auto& uv = temp_output_.uvs.back();
    Stream >> uv.x >> uv.y;
}


 // 法線ベクトルの読み込み
void WavefrontobjLoader::loadVertexNormal( std::istream& Stream )
{
    temp_output_.normals.emplace_back();
    auto& norm = temp_output_.normals.back();
    Stream >> norm.x >> norm.y >> norm.z;

    // 右手座標系のモデルは変換する
    if( temp_output_.coordinate_system == CoordinateSystem::kRightHand )
        norm.z *= -1.0F;
}


 // 面の読み込み
void WavefrontobjLoader::loadFace( std::istream& Stream )
{
    auto group_itr = temp_output_.groups.find(temp_output_.loading_group_name);

    // 頂点インデックス追加
    size_t index = group_itr->second.num_vertices;
    temp_output_.index_buf.push_back( index + 2U );
    temp_output_.index_buf.push_back( index + 1U );
    temp_output_.index_buf.push_back( index );
    group_itr->second.num_vertices += 3U;

    // 頂点バッファ用データ追加
    std::string data;
    int pos_idx;
    int uv_idx;
    int nrm_idx;
    for( int i = 0; i < 3; ++i )
    { // 3頂点
        Stream >> data;
        sscanf_s( data.c_str(), "%d/%d/%d", &pos_idx, &uv_idx, &nrm_idx );

        temp_output_.positions_buf.push_back( temp_output_.positions.at(pos_idx-1) );
        temp_output_.uvs_buf.push_back( temp_output_.uvs.at(uv_idx-1) );
        temp_output_.normals_buf.push_back( temp_output_.normals.at(nrm_idx-1) );
    }
}


 // グループ名読み込み
void WavefrontobjLoader::loadGroupName( std::istream& Stream )
{
    Stream >> temp_output_.loading_group_name;

    auto find_itr = temp_output_.groups.find(temp_output_.loading_group_name);
    if( find_itr == temp_output_.groups.end() )
    { // グループの新規追加
        temp_output_.groups.emplace( temp_output_.loading_group_name, Group{} );
    }
}


 // 使用マテリアル名読み込み
void WavefrontobjLoader::loadUseMaterialName( std::istream& Stream )
{
    auto group_itr = temp_output_.groups.find( temp_output_.loading_group_name );
    if( group_itr != temp_output_.groups.end() )
    {
        Stream >> group_itr->second.material_name;
    }
}


 // 使用マテリアルの読み込み
void WavefrontobjLoader::loadMaterialFile( std::istream& Stream )
{
    std::string data;
    Stream >> data;
    std::fstream mtl_stream{ data };
    if( !mtl_stream ) return;

    while( mtl_stream >> data )
    {
        auto find_itr = kLoadFunctions.find( data.c_str() );
        if( find_itr != kLoadFunctions.end() )
            // コマンドに対応した処理を呼び出す
            (this->*find_itr->second)(mtl_stream);
    }
    mtl_stream.close();
}


 // マテリアル名の読み込み
void WavefrontobjLoader::loadMaterialName( std::istream& Stream )
{
    Stream >> temp_output_.loading_material_name;
}


 // テクスチャの読み込み
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>
WavefrontobjLoader::loadTexture( const std::string& FilePath )
{
    auto* loader = getManager()->getTextureLoader();
    auto texture = loader->load( FilePath );
    
    if( !texture ) return nullptr;
    return *texture;
}


/******************************************************************************

	others

******************************************************************************/
 // 初期データからバッファを作成
template <class DataType>
bool createBuffer( ID3D11Device* Device, D3D11_BUFFER_DESC* Desc, const std::vector<DataType>& Source, ID3D11Buffer** Out )
{
    Desc->ByteWidth = sizeof(DataType) * Source.size();
    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem = Source.data();

    return SUCCEEDED( Device->CreateBuffer(Desc, &srd, Out) );
}
// 頂点バッファを作成する
DetailedReturnValue<bool> createVertexBuffers(
    ID3D11Device* Device,
    const std::vector<VertexPositionType>& Positions,
    const std::vector<VertexUVType>& UVs,
    const std::vector<VertexNormalType>& Normals,
    const std::vector<uint32_t>& Indices,
    ID3D11Buffer** OutPos, ID3D11Buffer** OutUV, ID3D11Buffer** OutNorm, ID3D11Buffer** OutIdx )
{
    using namespace Microsoft::WRL;

    D3D11_BUFFER_DESC buffer_desc{};
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    ComPtr<ID3D11Buffer> pos{};
    if( !createBuffer(Device, &buffer_desc, Positions, &pos) )
        return { Failure{}, "座標用バッファの作成に失敗" };
    ComPtr<ID3D11Buffer> uv{};
    if( !createBuffer(Device, &buffer_desc, UVs, &uv) )
        return { Failure{}, "UV座標用バッファの作成に失敗" };
    ComPtr<ID3D11Buffer> norm{};
    if( !createBuffer(Device, &buffer_desc, Normals, &norm) )
        return { Failure{}, "法線用バッファの作成に失敗" };
    buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ComPtr<ID3D11Buffer> idx{};
    if( !createBuffer(Device, &buffer_desc, Indices, &idx) )
        return { Failure{}, "インデックス用バッファの作成に失敗" };

    *OutPos = pos.Get(); pos->AddRef();
    *OutUV = uv.Get(); uv->AddRef();
    *OutNorm = norm.Get(); norm->AddRef();
    *OutIdx = idx.Get(); idx->AddRef();
    return Success{};
}

END_EGEG
// EOF
