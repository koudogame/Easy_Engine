// 作成者 : 板場
#include "shader_loader_d3d11.hpp"
#include <fstream>
#include "vertex_shader_d3d11.hpp"
#include "geometry_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"

namespace
{
    size_t getBinaryLength( std::fstream& FileStream );
} // !unnamed namespace 

BEGIN_EGEG
// ShaderLoaderD3D11
/*===========================================================================*/
// コンストラクタ
ShaderLoaderD3D11::ShaderLoaderD3D11( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}
// デストラクタ
ShaderLoaderD3D11::~ShaderLoaderD3D11()
{
    p_device_->Release();
}

// 頂点シェーダ―の読み込み
bool ShaderLoaderD3D11::loadVertexShader( const std::string& Path, IVertexShader** ppShader )
{
    // シェーダーファイル読み込み
    std::fstream stream( Path, std::ios::binary | std::ios::in );
    if( !stream ) return false;
    size_t file_size = ::getBinaryLength(stream);
    char* blob = new char[ file_size ];
    stream.read( blob, file_size );
    stream.close();

    // シェーダーオブジェクトの生成
    ID3D11VertexShader* created_vs;
    if( FAILED(p_device_->CreateVertexShader(blob, file_size, nullptr, &created_vs)) )
    {
        delete[] blob;
        return false;
    }

    // 頂点入力レイアウト
    ID3D11InputLayout* input_layout;
    if( FAILED(p_device_->CreateInputLayout(
        VertexShaderD3D11::kVertexInputLayout,
        sizeof VertexShaderD3D11::kVertexInputLayout / sizeof VertexShaderD3D11::kVertexInputLayout[0],
        blob,
        file_size,
        &input_layout)) )
    {
        created_vs->Release();
        delete[] blob;
        return false;
    }
    delete[] blob;

    *ppShader = new VertexShaderD3D11( created_vs , input_layout );
    input_layout->Release();
    created_vs->Release();

    return true;
}

// ジオメトリシェーダーの読み込み
bool ShaderLoaderD3D11::loadGeometryShader( const std::string& Path, IGeometryShader** ppShader )
{
    // シェーダーファイルの読み込み
    std::fstream stream( Path, std::ios::binary | std::ios::in );
    if( !stream ) return false;
    size_t file_size = ::getBinaryLength( stream );
    char* blob;
    { blob = new char[ file_size ]; }
    stream.read( blob, file_size );
    stream.close();

    // シェーダーオブジェクトの生成
    ID3D11GeometryShader* created_gs;
    if( FAILED(p_device_->CreateGeometryShader(blob, file_size, nullptr, &created_gs)) )
    {
        delete[] blob;
        return false;
    }
    delete[] blob;

    *ppShader = new GeometryShaderD3D11( created_gs );
    created_gs->Release();

    return true;
}

// ピクセルシェーダーの読み込み
bool ShaderLoaderD3D11::loadPixelShader( const std::string& Path, IPixelShader** ppShader )
{
    // シェーダーファイルの読み込み
    std::fstream stream( Path, std::ios::binary | std::ios::in );
    if( !stream ) return false;
    size_t file_size = ::getBinaryLength( stream );
    char* blob = new char[ file_size ];
    stream.read( blob, file_size );
    stream.close();

    // シェーダーオブジェクトの生成
    ID3D11PixelShader* created_ps;
    if( FAILED(p_device_->CreatePixelShader(blob, file_size, nullptr, &created_ps)) )
    {
        delete[] blob;
        return false;
    }
    delete[] blob;

    *ppShader = new PixelShaderD3D11( created_ps );
    created_ps->Release();

    return true;
}
END_EGEG

namespace
{
    // ファイルのサイズを取得する
    // この関数を抜けた後、ストリームはファイル始点を指す。
    //
    // in Stream : ファイルストリーム
    //
    // return ファイルのサイズ
    size_t getBinaryLength( std::fstream& Stream )
    {
        Stream.seekg( 0, std::ios::end );
        auto end = Stream.tellg();
        Stream.clear();
        Stream.seekg( 0, std::ios::beg );
        auto beg = Stream.tellg();
        size_t size = static_cast<size_t>( end - beg );

        return size;
    }
} // !unnamed namespace
// EOF
