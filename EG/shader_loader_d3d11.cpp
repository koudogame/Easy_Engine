// 作成者 : 板場
#include "shader_loader_d3d11.hpp"
#include <fstream>
#include "vertex_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"

BEGIN_EGEG
// 関数の実装
/*===========================================================================*/
// 頂点シェーダ―のロード
bool ShaderLoaderD3D11::loadVertexShader( const char* Path, IVertexShader** ppOut )
{
    auto find = vertex_shaders_.find( Path );

    // キャッシュにある場合
    if( find != vertex_shaders_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // ファイルオープン
        std::fstream stream( Path, std::ios::binary | std::ios::in );
        if( stream.is_open() == false ) return false;

        // データ読み込み
        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        UINT size = static_cast<UINT>(end - beg );
        char* blob = new char[size];
        stream.read( blob, size );
        stream.close();

        // 頂点シェーダ―の生成
        ID3D11VertexShader* p_d3d11vs;
        if( FAILED(p_device_->CreateVertexShader(blob, size, nullptr, &p_d3d11vs)) )
            return false;

        VertexShaderD3D11 *p_vs = new VertexShaderD3D11( p_d3d11vs );
        p_d3d11vs->Release();

        *ppOut = p_vs;
    }

    return true;
}

// ピクセルシェーダーのロード
bool ShaderLoaderD3D11::loadPixelShader( const char* Path, IPixelShader** ppOut )
{
    auto find = pixel_shaders_.find( Path );

    // キャッシュにある場合
    if( find != pixel_shaders_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // ファイルオープン
        std::fstream stream( Path, std::ios::binary | std::ios::in );
        if( stream.is_open() == false ) return false;

        // データ読み込み
        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        UINT size = static_cast<UINT>( end - beg );
        char* blob = new char[size];
        stream.read( blob, size );
        stream.close();

        // ピクセルシェーダ―の作成
        ID3D11PixelShader* p_d3d11ps;
        if( FAILED(p_device_->CreatePixelShader(blob, size, nullptr, &p_d3d11ps)) )
            return false;

        PixelShaderD3D11 *p_ps = new PixelShaderD3D11( p_d3d11ps );
        p_d3d11ps->Release();

        *ppOut = p_ps;
    }

    return true;
}
END_EGEG
// EOF
