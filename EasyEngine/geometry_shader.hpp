///
/// @file   geometry_shader.hpp
/// @author ��
///
/// @brief  �W�I���g���V�F�[�_�[
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class IGeometryShader :
    public Interface
{
protected :
    virtual ~IGeometryShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
