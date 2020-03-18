// 作成者 : 板場
#include "WavefrontOBJ_loader.hpp"

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

    if( mesh_itr != mesh_cache_.end() )
    { // キャッシュに存在しない場合
        // 新規に読み込み、キャッシュに保存
        /*auto mesh = loadMeshFromFile( FileName.c_str() );
        if( mesh ) mesh_cache_.emplace( std::move(FileName), mesh.get() );

        return mesh;*/
    }
    else if( mesh_itr->second.expired() )
    { // キャッシュにあるが、既に破棄されていた場合
        // 再度読み込み、対応する位置に保管
        //auto mesh = loadMeshFromFile( FileName.c_str() );
        //mesh_itr->second = mesh.get();

        //// Attention : このブロックを抜けるとスマートポインタのデストラクタが呼び出され、
        ////             確保したメモリが解放されるのでこのブロック内でreturn文を宣言している。
        //return mesh;
    }

    // キャッシュされているメッシュを返却
    return DetailedReturnValue<std::shared_ptr<const Mesh>>( true, mesh_itr->second );
}

// 
END_EGEG
// EOF
