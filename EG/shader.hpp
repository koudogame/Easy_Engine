///
/// @file   shader.hpp
/// @author ��
///
/// @brief  �V�F�[�_�[�̃C���^�[�t�F�C�X
///
#ifndef INCLUDED_EG_EG_SHADER_HEADER_
#define INCLUDED_EG_EG_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class IShader :
    public SharedObject
{
protected :
    virtual ~IShader() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_HEADER_
/// EOF
