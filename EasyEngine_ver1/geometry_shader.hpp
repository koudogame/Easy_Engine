///
/// @file   geometry_shader.hpp
/// @author 板場
///
/// @brief  ジオメトリシェーダー
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
class IGeometryShader :
    public SharedObject
{
protected :
    virtual ~IGeometryShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
