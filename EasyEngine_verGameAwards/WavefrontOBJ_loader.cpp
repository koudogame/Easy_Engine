// 作成者 : 板場
#include "WavefrontOBJ_loader.hpp"
#include <fstream>

namespace
{
    template <class VertexDataType>
    ID3D11Buffer* createBufferFromData( ID3D11Device*, D3D11_BUFFER_DESC*, const std::vector<VertexDataType>& );
} // unnamed namespace

BEGIN_EGEG

// WavefrontOBJ 関数定義
/*===========================================================================*/
// .objファイルからメッシュデータをロード
// キャッシュにデータがある場合、コピーを返却
//
// 読み込んだメッシュデータはキャッシュに格納する。
DetailedReturnValue<std::shared_ptr<const Mesh>> WavefrontOBJLoader::loadMesh(
    std::string FileName )
{
    auto mesh_itr = mesh_cache_.find( FileName ); // キャッシュからメッシュデータを取得

    if( mesh_itr == mesh_cache_.end() )
    { // キャッシュに存在しない場合
        // 新規に読み込み、キャッシュに保存
        auto mesh = loadMeshFromFile( FileName.c_str() );
        if( mesh ) mesh_cache_.emplace( std::move(FileName), mesh.get() );

        return mesh;
    }
    else if( mesh_itr->second.expired() )
    { // キャッシュにあるが、既に破棄されていた場合
        // 再度読み込み保管。初回読み込みではないので、ロードのチェックを行っていない。
        auto mesh = loadMeshFromFile( FileName.c_str() );
        mesh_itr->second = mesh.get();

        // Attention : このブロックを抜けるとスマートポインタのデストラクタが呼び出され、
        //             確保したメモリが解放されるのでこのブロック内でreturn文を宣言している。
        return mesh;
    }

    // キャッシュされているメッシュを返却
    return DetailedReturnValue<std::shared_ptr<const Mesh>>( true, mesh_itr->second );
}

// .objファイルからメッシュデータをロード
DetailedReturnValue<std::shared_ptr<const Mesh>> WavefrontOBJLoader::loadMeshFromFile( const char* FileName )
{
    using RetTy = DetailedReturnValue<std::shared_ptr<const Mesh>>;

    // ファイルオープン
    std::fstream stream( FileName );
    if( !stream )
    { // ファイルオープン失敗
        return RetTy( false, nullptr, "ファイルオープン失敗" );
    }

    std::vector<VertexPositionType> position; position.reserve( 256U );
    std::vector<VertexUVType>       texcoord; texcoord.reserve( 256U );
    std::vector<VertexNormalType>   normal;   normal.reserve( 256U );
    std::vector<UINT>               index_for_buf;    index_for_buf.reserve( 1024U );
    std::vector<VertexPositionType> position_for_buf; position_for_buf.reserve( 256U );
    std::vector<VertexUVType>       texcoord_for_buf; texcoord_for_buf.reserve( 256U );
    std::vector<VertexNormalType>   normal_for_buf;   normal_for_buf.reserve( 256U );

    std::string command;    // コマンド格納用バッファ
    UINT start_idx = 0U;    // ポリゴンの開始インデックス
    VertexPositionType vp;  // 頂点座標用一時オブジェクト
    VertexUVType       vt;  // UV座標用一時オブジェクト
    VertexNormalType   vn;  // 法線ベクトル用一時オブジェクト
    while( stream >> command )
    { // ファイルからデータを読み込む
        if( command == "v" )
        { // 頂点座標の読み込み
            stream >> vp.x >> vp.y >> vp.z;
            position.push_back( vp );
        }
        else if( command == "vt" )
        { // テクスチャ座標の読み込み
            stream >> vt.x >> vt.y;
            texcoord.push_back( vt );
        }
        else if( command == "vn" )
        { // 法線ベクトルの読み込み
            stream >> vn.x >> vn.y >> vn.z;
            normal.push_back( vn );
        }
        else if( command == "f" )
        { // 面(三角形ポリゴン)の読み込み
            index_for_buf.push_back( start_idx+ 2 );
            index_for_buf.push_back( start_idx+ 1 );
            index_for_buf.push_back( start_idx+ 0 );

            start_idx += 3;
        
            std::string str;
            int pos_idx;
            int uv_idx;
            int norm_idx;
            for( int i = 0; i < 3; ++i )
            { // ポリゴンを形成する３頂点を読み込む
                stream >> str;
                sscanf_s( str.data(),
                    "%d/%d/%d",
                    &pos_idx, &uv_idx, &norm_idx
                );

                // 頂点をデータ化
                position_for_buf.push_back( position.at(pos_idx - 1) );
                texcoord_for_buf.push_back( texcoord.at(uv_idx - 1) );
                normal_for_buf.push_back( normal.at(norm_idx - 1) );
            }
        }
    }
    stream.close();

    // バッファオブジェクトの作成
    D3D11_BUFFER_DESC desc {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    ID3D11Buffer* position_buffer = ::createBufferFromData(device_.Get(), &desc, position_for_buf );
    if( position_buffer == nullptr )
    { // バッファオブジェクトの作成に失敗
        return RetTy( false, nullptr, "頂点座標用頂点バッファの作成に失敗" );
    }

    ID3D11Buffer* texcoord_buffer = ::createBufferFromData(device_.Get(), &desc, texcoord_for_buf );
    if( texcoord_buffer == nullptr )
    { // バッファオブジェクトの作成に失敗
        position_buffer->Release();
        return RetTy( false, nullptr, "UV座標用頂点バッファの作成に失敗" );
    }

    ID3D11Buffer* normal_buffer = ::createBufferFromData(device_.Get(), &desc, normal_for_buf );
    if( normal_buffer == nullptr )
    { // バッファオブジェクトの作成に失敗
        position_buffer->Release();
        texcoord_buffer->Release();
        return RetTy( false, nullptr, "法線ベクトル用頂点バッファの作成に失敗" );
    }
    

    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ID3D11Buffer* index_buffer = ::createBufferFromData(device_.Get(), &desc, index_for_buf );
    if( index_buffer == nullptr )
    { // バッファオブジェクトの作成に失敗
        position_buffer->Release();
        texcoord_buffer->Release();
        normal_buffer->Release();
        return RetTy( false, nullptr, "インデックスバッファの作成に失敗" );
    }
    
    // メッシュデータの作成
    Mesh* mesh = new Mesh();
    mesh->setVertexBuffer( kVertexPositionSemantic, position_buffer );
    mesh->setVertexBuffer( kVertexUVSemantic, texcoord_buffer );
    mesh->setVertexBuffer( kVertexNormalSemantic, normal_buffer );
    mesh->setIndexBuffer( index_buffer );
    mesh->setNumVertices( index_for_buf.size() );
    position_buffer->Release();
    texcoord_buffer->Release();
    normal_buffer->Release();
    index_buffer->Release();

    return RetTy(true, std::unique_ptr<Mesh>(mesh) );
}

END_EGEG

namespace
{
    template <class VertexDataType>
    ID3D11Buffer* createBufferFromData( ID3D11Device* Device, D3D11_BUFFER_DESC* Desc,  const std::vector<VertexDataType>& Source )
    {
        ID3D11Buffer* buffer = nullptr;
        Desc->ByteWidth = sizeof( VertexDataType ) * Source.size();
        D3D11_SUBRESOURCE_DATA srd{};
        srd.pSysMem = Source.data();

        Device->CreateBuffer( Desc, &srd, &buffer );
        return buffer;
    }
} // unnamed namespace
// EOF
