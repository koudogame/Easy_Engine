// 作成者 : 板場
#include "shader_loader_windows.hpp"
#include <fstream>
#include "vertex_shader_windows.hpp"
#include "geometry_shader_windows.hpp"
#include "pixel_shader_windows.hpp"

namespace
{
    size_t loadBinary( const std::string&, char* );
} // !unnamed namespace 

BEGIN_EGEG
// ShaderLoaderWindows
/*===========================================================================*/
// コンストラクタ
ShaderLoaderWindows::ShaderLoaderWindows( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}
// デストラクタ
ShaderLoaderWindows::~ShaderLoaderWindows()
{
    p_device_->Release();
}

// 頂点シェーダ―の読み込み
bool ShaderLoaderWindows::loadVertexShader( const std::string& Path, IVertexShader** ppShader )
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

    *ppShader = new VertexShaderWindows( created_vs );
    created_vs->Release();

    return true;
}

// ジオメトリシェーダーの読み込み
bool ShaderLoaderWindows::loadGeometryShader( const std::string& Path, IGeometryShader** ppShader )
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

    *ppShader = new GeometryShaderWindows( created_gs );
    created_gs->Release();

    return true;
}

// ピクセルシェーダーの読み込み
bool ShaderLoaderWindows::loadPixelShader( const std::string& Path, IPixelShader** ppShader )
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

    *ppShader = new PixelShaderWindows( created_ps );
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
