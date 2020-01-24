// 作成者 : 板場
#include "shader_loader_d3d11.hpp"
#include <fstream>
#include "vertex_shader_d3d11.hpp"
#include "geometry_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"

namespace
{
    size_t loadBinary( const std::string&, char* );
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
    ID3D11VertexShader* created_vs;
    char* blob = nullptr;
    size_t size = ::loadBinary( Path, blob );
    if( size == 0U ||
        FAILED(p_device_->CreateVertexShader(blob, size, nullptr, &created_vs)) )
    {
        delete[] blob;
        return false;
    }

    // 頂点入力レイアウト

    *ppShader = new VertexShaderD3D11( created_vs );
    created_vs->Release();

    return true;
}

// ジオメトリシェーダーの読み込み
bool ShaderLoaderD3D11::loadGeometryShader( const std::string& Path, IGeometryShader** ppShader )
{
    ID3D11GeometryShader* created_gs;
    char* blob = nullptr;
    size_t size = ::loadBinary( Path, blob );
    if( size == 0U ||
        FAILED(p_device_->CreateGeometryShader(blob, size, nullptr, &created_gs)) )
    {
        delete[] blob;
        return false;
    }

    *ppShader = new GeometryShaderD3D11( created_gs );
    created_gs->Release();

    return true;
}

// ピクセルシェーダーの読み込み
bool ShaderLoaderD3D11::loadPixelShader( const std::string& Path, IPixelShader** ppShader )
{
    ID3D11PixelShader* created_ps;
    char* blob = nullptr;
    size_t size = ::loadBinary( Path, blob );
    if( size == 0U ||
        FAILED(p_device_->CreatePixelShader(blob, size, nullptr, &created_ps)) )
    {
        delete[] blob;
        return false;
    }

    *ppShader = new PixelShaderD3D11( created_ps );
    created_ps->Release();

    return true;
}
END_EGEG

namespace
{
    // ファイルからバイナリデータを読み込む
    // Bufferにはファイルの大きさに対応したメモリブロックを割り当てます。解放してください。
    //
    // in FilePath : 読み込むファイルのパス
    // out Buffer : 読み込んだデータを格納するバッファ(確保前)
    //
    // return 読み込んだファイルのサイズ
    size_t loadBinary( const std::string& FilePath, char* Buffer )
    {
        // ファイルオープン
        std::fstream stream( FilePath, std::ios::binary | std::ios::in );
        if( stream.is_open() == false ) return 0U;

        // データ読み込み
        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        size_t size = static_cast<size_t>( end - beg );
        Buffer = new char[ size ];
        stream.read( Buffer, size );
        stream.close();

        return size;
    }
} // !unnamed namespace
// EOF
