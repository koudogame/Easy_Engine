///
/// @file   shader_loader_d3d11.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_D3D11_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_D3D11_HEADER_
#include <d3d11.h>
#include "shader_loader.hpp"
BEGIN_EGEG
///
/// @class ShaderLoaderD3D11
///
/// @brief  DirectX11用シェーダーローダー
///
class ShaderLoaderD3D11 :
    public IShaderLoader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pDevice : D3Dデバイス
    ///
    ShaderLoaderD3D11( ID3D11Device* pDevice );

// IShaderLoader
/*-----------------------------------------------------------------*/
    bool loadVertexShader( const std::string&, IVertexShader** ) override;
    bool loadGeometryShader( const std::string&, IGeometryShader** ) override;
    bool loadPixelShader( const std::string&, IPixelShader** ) override;

private :
    ~ShaderLoaderD3D11();
    ID3D11Device* p_device_;    /// D3Dデバイス
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_D3D11_HEADER_
/// EOF
