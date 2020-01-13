///
/// @file   shader_2d_d3d11.hpp
/// @author 板場
///
/// @brief  2D用シェーダー
///
#ifndef INCLUDED_EG_EG_SIMPLE_SHADER_HEADER_
#define INCLUDED_EG_EG_SIMPLE_SHADER_HEADER_
#include <d3d11.h>
#include "shader_d3d11.hpp"
BEGIN_EGEG
class Shader2DD3D11 :
    public IShaderD3D11
{
public :
    Shader2DD3D11();
    void setShaders( ID3D11DeviceContext* pDeviceContext );

private :
    ID3D11VertexShader*  p_vs_;
    ID3D11PixelShader*   p_ps_;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SIMPLE_SHADER_HEADER_
/// EOF
