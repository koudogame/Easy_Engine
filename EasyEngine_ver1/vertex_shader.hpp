///
/// @file   vertex_shader.hpp
/// @author ��
///
/// @brief  ���_�V�F�[�_�\
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
class IVertexShader :
    public SharedObject
{
protected :
    virtual ~IVertexShader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_HEADER_
/// EOF