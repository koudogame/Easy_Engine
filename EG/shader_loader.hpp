///
/// @file   shader_loader.hpp
/// @author ��
///
/// @brief  �V�F�[�_�[���[�_�[�̃C���^�[�t�F�C�X
///
#ifndef INCLUDED_EG_EG_SHADER_LOADER_HEADER_
#define INCLUDED_EG_EG_SHADER_LOADER_HEADER_
#include "interface.hpp"
#include "vertex_shader.hpp"
#include "pixel_shader.hpp"
BEGIN_EG_EG
class IShaderLoader :
    public Interface
{
public :
    ///
    /// @brief  ���_�V�F�[�_�[�̃��[�h
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�t�@�C���̃p�X
    /// @param[out] ppOutShader : ���[�h�����V�F�[�_�\���󂯎��C���^�[�t�F�C�X
    ///
    /// @return ���[�h�ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    virtual bool loadVertexShader( const char* FilePath, IVertexShader** ppOutShader ) = 0;

    ///
    /// @brief  �s�N�Z���V�F�[�_�|�̃��[�h
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�t�@�C���̃p�X
    /// @param[out] ppOutShader : ���[�h�����V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return ���[�h�ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    virtual bool loadPixelShader( const char* FilePath, IPixelShader** ppOutShader ) = 0;

protected :
    virtual ~IShaderLoader() = default;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_SHADER_LOADER_HEADER_
/// EOF
