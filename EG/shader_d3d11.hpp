///
/// @file   shader_d3d11.hpp 
/// @author 板場
///
/// @brief  D3D11用シェーダーインターフェイス
///
#ifndef INCLUDED_EG_EG_SHADER_D3D11_HEADER_
#define INCLUDED_EG_EG_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "shader.hpp"
BEGIN_EGEG
class IShaderD3D11 :
    public IShader
{
public :
    ///
    /// @brief  パイプラインにシェーダーをセットする。
    ///
    /// @param[in] pDeviceContext : シェーダーオブジェクトをセットするパイプライン
    ///
    void setShaders( ID3D11DeviceContext* pDeviceContext );

protected :
    virtual ~IShaderD3D11() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_D3D11_HEADER_
/// EOF
