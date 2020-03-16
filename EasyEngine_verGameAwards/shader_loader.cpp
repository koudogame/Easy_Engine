// 作成者 : 板場
#include "shader_loader.hpp"
#include <fstream>

BEGIN_EGEG

// ShaderLoader 関数実装
/*===========================================================================*/
// ファイルサイズの取得
// 引数のファイルストリームは既にファイルを開いているものとする。
// この関数を抜けた後、ストリームはファイル始点を指す。
//
// in Stream : サイズを取得するファイルストリーム
//
// return ファイルサイズ
size_t ShaderLoader::getFileSize( std::fstream& Stream )
{
    Stream.seekg( 0, std::ios::end );
    auto end = Stream.tellg();
    Stream.clear();
    Stream.seekg( 0, std::ios::beg );
    auto beg = Stream.tellg();
    
    return static_cast<size_t>( end - beg );
}

END_EGEG
// EOF
