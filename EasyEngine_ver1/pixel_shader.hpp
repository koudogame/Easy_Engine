///
/// @file   pixel_shader.hpp
/// @author ��
///
/// @brief  �s�N�Z���V�F�[�_�\
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
class IPixelShader :
    public SharedObject
{
protected :
    virtual ~IPixelShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
