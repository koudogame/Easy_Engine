///
/// @file   pixel_shader.hpp
/// @author 板場
///
/// @brief  ピクセルシェーダインターフェイス
///
#ifndef INCLUDED_EG_EG_PIXEL_SHADER_HEADER_
#define INCLUDED_EG_EG_PIXEL_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class IPixelShader :
    public Interface
{
public :
protected :
    virtual ~IPixelShader() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_PIXEL_SHADER_HEADER_
/// EOF
