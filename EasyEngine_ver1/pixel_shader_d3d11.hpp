///
/// @file   pixel_shader_d3d11.hpp
/// @author 板場
///
/// @brief  DirectX11用ピクセルシェーダー
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_D3D11_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "pixel_shader.hpp"
BEGIN_EGEG
class PixelShaderD3D11 :
    public IPixelShader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pPixelShader : 保持するシェーダーオブジェクト
    ///
    PixelShaderD3D11( ID3D11PixelShader* pPixelShader ) :
        p_shader_( pPixelShader )
    {
        p_shader_->AddRef();
    }

    ///
    /// @brief  シェーダーオブジェクトの取得
    ///
    /// @return シェーダーオブジェクト
    ///
    ID3D11PixelShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

private :
    ~PixelShaderD3D11()
    {
        p_shader_->Release();
    }
    ID3D11PixelShader* p_shader_;   /// シェーダーオブジェクト
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_D3D11_HEADER_
/// EOF
