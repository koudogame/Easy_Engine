///
/// @file   shader_loader_d3d11.hpp
/// @author 板場
///
/// @brief  D3D11用シェーダーローダー
///
#ifndef INCLUDED_EG_EG_SHADER_LOADER_D3D11_HEADER_
#define INCLUDED_EG_EG_SHADER_LOADER_D3D11_HEADER_
#include <unordered_map>
#include <d3d11.h>
#include "shader_loader.hpp"
BEGIN_EGEG
class ShaderLoaderD3D11 :
    public IShaderLoader
{
public :
    ShaderLoaderD3D11( ID3D11Device* pDevice ) :
        p_device_( pDevice )
    {
        p_device_->AddRef();
    }

// IShaderLoader
/*-----------------------------------------------------------------*/
    bool loadVertexShader( const char*, IVertexShader** ) override;
    bool loadPixelShader( const char*, IPixelShader** ) override;

private :
    ~ShaderLoaderD3D11()
    {
        p_device_->Release();
    }

    ID3D11Device* p_device_;
    std::unordered_map<const char*, IVertexShader*> vertex_shaders_;   ///< 頂点シェーダ―キャッシュ
    std::unordered_map<const char*, IPixelShader*>  pixel_shaders_;    ///< ピクセルシェーダ―キャッシュ
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_SHADER_LOADER_D3D11_HEADER_
/// EOF
