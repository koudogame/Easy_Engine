///
/// @file   platform.hpp
/// @author ��
///
/// @brief  �v���b�g�t�H�[��
///
#ifndef INCLUDED_EGEG_PLATFORM_HEADER_
#define INCLUDED_EGEG_PLATFORM_HEADER_
#include "interface.hpp"
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class IPlatform :
    public Interface
{
public :
    ///
    /// @brief  �����_���[�̐���
    ///
    /// @return �������������_���[
    ///
    virtual IRenderer* createRenderer() const = 0;

    ///
    /// @brief  �V�F�[�_�[���[�_�[�̐���
    ///
    /// @return ���������V�F�[�_�[���[�_�[
    ///
    virtual IShaderLoader* createShaderLoader() const = 0;

    ///
    /// @brief  �e�N�X�`�����[�_�[�̐���
    ///
    /// @return ���������e�N�X�`�����[�_�[
    ///
    virtual ITextureLoader* createTextureLoader() const = 0;

protected :
    virtual ~IPlatform() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_HEADER_
/// EOF
