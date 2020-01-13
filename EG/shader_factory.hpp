///
/// @file  shader_factory.hpp
/// @author ��
///
/// @brief  �V�F�[�_�[�t�@�N�g���̃C���^�[�t�F�C�X
///
#ifndef INCLUDED_EG_EG_SHADER_FACTORY_HEADER_
#define INCLUDED_EG_EG_SHADER_FACTORY_HEADER_
#include "shader.hpp"
BEGIN_EGEG
class IShaderFactory :
    public Interface
{
public :
    ///
    /// @brief  �V�F�[�_�[�̐�������
    ///
    /// @param[in] ShaderName : ��������V�F�[�_�[�̖��O
    /// @param[out] ppOutShader : ���������V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    virtual bool create( const char* ShaderName, IShader** ppOutShader ) = 0;

protected :
    virtual ~IShaderFactory() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_FACTORY_HEADER_
/// EOF
