///
/// @file   pixel_shader.hpp
/// @author 板場
///
/// @brief  ピクセルシェーダ―
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class IPixelShader :
    public Interface
{
protected :
    virtual ~IPixelShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
