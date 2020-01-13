///
/// @file   pixel_shader_d3d11.hpp
/// @author 板場
///
/// @brief  D3D11用ピクセルシェーダー
///
#ifndef INCLUDED_EG_EG_PIXEL_SHADER_D3D11_HEADER_
#define INCLUDED_EG_EG_PIXEL_SHADER_D3D11_HEADER_
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
        p_pixel_shader_( pPixelShader )
    {
        p_pixel_shader_->AddRef();
    }

    ///
    /// @brief  保持しているシェーダーオブジェクトを取得します。
    ///
    /// @return 保持しているシェーダ―オブジェクトのアドレス
    ///
    ID3D11PixelShader* get() const { return p_pixel_shader_; }

private :
    ~PixelShaderD3D11()
    {
        p_pixel_shader_->Release();
    }

    ID3D11PixelShader* p_pixel_shader_;
};
END_EGEG
#endif  /// !INCLUDED_EG_EG_PIXEL_SHADER_D3D11_HEADER_
/// EOF
