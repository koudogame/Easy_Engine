// 作成者 : 板場
#include "WavefrontOBJ_loader.hpp"
#include <fstream>

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
    std::vector<UINT>               index;    index.reserve( 1024U );
    std::vector<VertexPositionType> position_for_buf; position_for_buf.reserve( 256U );
    std::vector<VertexUVType>       texcoord_for_buf; texcoord_for_buf.reserve( 256U );
    std::vector<VertexNormalType>   normal_for_buf;   normal_for_buf.reserve( 256U );

    std::string data_type;
    UINT start_idx = 0U;
    VertexPositionType vp;
    VertexUVType       vt;
    VertexNormalType   vn;
    while( stream >> data_type )
    { // ファイルから頂点データを読み込む
        if( data_type == "v" )
        { // 頂点座標の読み込み
            stream >> vp.x >> vp.y >> vp.z;
            position.push_back( vp );
        }
        else if( data_type == "vt" )
        { // テクスチャ座標の読み込み
            stream >> vt.x >> vt.y;
            texcoord.push_back( vt );
        }
        else if( data_type == "vn" )
        { // 法線ベクトルの読み込み
            stream >> vn.x >> vn.y >> vn.z;
            normal.push_back( vn );
        }
        else if( data_type == "f" )
        { // 面(ポリゴン)の読み込み
            index.push_back( start_idx+ 2 );
            index.push_back( start_idx+ 1 );
            index.push_back( start_idx+ 0 );

            start_idx += 3;
        
            std::string str;
            int pos_idx;
            int uv_idx;
            int norm_idx;

            for( int i = 0; i < 3; ++i )
            {
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
    ID3D11Buffer* position_buffer;
    D3D11_BUFFER_DESC desc {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof( VertexPositionType ) * position_for_buf.size();
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA srd {};
    srd.pSysMem = position_for_buf.data();
    device_->CreateBuffer( &desc, &srd, &position_buffer );

    ID3D11Buffer* index_buffer;
    desc.ByteWidth = sizeof( UINT ) * index.size();
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    srd.pSysMem = index.data();
    device_->CreateBuffer( &desc, &srd, &index_buffer );
    
    // メッシュデータの作成
    Mesh* mesh = new Mesh();
    mesh->setVertexBuffer( kVertexPositionSemantic, position_buffer );
    mesh->setIndexBuffer( index_buffer );
    mesh->setNumVertices( index.size() );
    position_buffer->Release();
    index_buffer->Release();

    return RetTy(true, std::unique_ptr<Mesh>(mesh) );
}
END_EGEG
// EOF
