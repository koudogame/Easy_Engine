///
/// @file   geometry_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
///
/// @class IGeometryShader
///
/// @brief  �W�I���g���V�F�[�_�[
///
class IGeometryShader :
    public SharedObject
{
protected :
    virtual ~IGeometryShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
