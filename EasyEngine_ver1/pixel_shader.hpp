///
/// @file   pixel_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
///
/// @class  IPixelShader
///
/// @brief  ピクセルシェーダ―
///
class IPixelShader :
    public SharedObject
{
protected :
    virtual ~IPixelShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
