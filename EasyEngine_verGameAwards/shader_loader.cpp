// 作成者 : 板場
#include "shader_loader.hpp"
#include <fstream>

namespace
{
    size_t getFileSize( std::fstream& );
} // unnamed namespace

BEGIN_EGEG

// ShaderLoader 関数実装
/*===========================================================================*/
// 頂点シェーダーのロード
DetailedReturnValue<bool> ShaderLoader::load( const TCHAR* FileName, const D3D11_INPUT_ELEMENT_DESC* InputElementDescs, size_t NumElements, ID3D11VertexShader** OutShader, ID3D11InputLayout** OutInputLayout )
{
    // ファイルオープン
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) return ReturnValue( false, "シェーダ―ファイルのオープン失敗" );

    // シェーダー読み込み
    size_t filesize = ::getFileSize( stream );
    char* blob = new char[filesize];
    stream.read( blob, filesize );
    stream.close();

    // シェーダーオブジェクトの生成
    HRESULT hr = device_->CreateVertexShader(
        blob,
        filesize,
        nullptr,
        OutShader );
    if( FAILED(hr) )
    {
        delete[] blob;
        return ReturnValue( false, "シェーダーオブジェクトの生成失敗" );
    }

    // 頂点入力レイアウトオブジェクトの生成
    hr = device_->CreateInputLayout(
        InputElementDescs,
        NumElements,
        blob,
        filesize,
        OutInputLayout );
    if( FAILED(hr) )
    {
        delete[] blob;
        return ReturnValue( false, "入力レイアウトオブジェクトの生成失敗" );
    }

    delete[] blob;
    return true;
}

// ジオメトリシェーダーのロード
DetailedReturnValue<bool> ShaderLoader::load( const TCHAR* FileName, ID3D11GeometryShader** OutShader )
{
    // ファイルオープン
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) return ReturnValue( false, "シェーダ―ファイルのオープン失敗" );

    // シェーダ―読み込み
    size_t filesize = ::getFileSize( stream );
    char* blob = new char[ filesize ];
    stream.read( blob, filesize );
    stream.close();

    // シェーダ―オブジェクトの生成
    HRESULT hr = device_->CreateGeometryShader(
        blob,
        filesize,
        nullptr,
        OutShader );
    delete[] blob;
    if( FAILED(hr) ) return ReturnValue( false, "シェーダ―オブジェクトの生成失敗" );

    return true;
}

// ピクセルシェーダーのロード
DetailedReturnValue<bool> ShaderLoader::load( const TCHAR* FileName, ID3D11PixelShader** OutShader )
{
    // ファイルオープン
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) return ReturnValue( false, "シェーダーファイルのオープン失敗" );

    // シェーダ―読み込み
    size_t filesize = ::getFileSize( stream );
    char* blob = new char[ filesize ];
    stream.read( blob, filesize );
    stream.close();

    // シェーダーオブジェクトの生成
    HRESULT hr = device_->CreatePixelShader(
        blob,
        filesize,
        nullptr,
        OutShader );
    delete[] blob;
    if( FAILED(hr) ) return ReturnValue( false, "シェーダーオブジェクトの生成失敗" );

    return true;
}
END_EGEG


namespace
{
// ファイルサイズの取得
// 引数のファイルストリームは既にファイルを開いているものとする。
// この関数を抜けた後、ストリームはファイル始点を指す。
//
// in Stream : サイズを取得するファイルストリーム
//
// return ファイルサイズ
size_t getFileSize( std::fstream& Stream )
{
    Stream.seekg( 0, std::ios::end );
    auto end = Stream.tellg();
    Stream.clear();
    Stream.seekg( 0, std::ios::beg );
    auto beg = Stream.tellg();
    
    return static_cast<size_t>( end - beg );
}
} // unnamed namespace
// EOF
