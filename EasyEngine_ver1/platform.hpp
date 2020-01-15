///
/// @file   platform.hpp
/// @author ��
///
/// @brief  �v���b�g�t�H�[��
///
#ifndef INCLUDED_EGEG_PLATFORM_HEADER_
#define INCLUDED_EGEG_PLATFORM_HEADER_
#include <functional>
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
    /// @brief   ���C�����[�v
    /// @details �����̊֐��ɂ���<br>
    ///          �����ɂ͌Ăяo�����̌o�ߎ���(: �~���b)��^���܂��B<br>
    ///          �߂�l��[ false ] ���Ԃ��Ă����ꍇ�A���[�v���I�����܂��B
    ///
    /// @param[in] pUpdateFunction : ���[�v���Ɏ��s����Q�[���̍X�V�֐�
    ///
    virtual void MainLoop( std::function<bool(long long)> pUpdateFunction ) = 0;

    ///
    /// @brief  �_�C�A���O�{�b�N�X�̕\��
    ///
    /// @param[in] Message : �_�C�A���O�{�b�N�X�ɕ\�����镶����
    ///
    virtual void showDialogBox( const wchar_t* Message ) = 0;

    ///
    /// @brief   �����_���[�̎擾
    ///
    /// @return  �����_���[�̃A�h���X
    ///
    virtual IRenderer* getRenderer() const = 0;
    ///
    /// @brief   �V�F�[�_�[���[�_�[�̎擾
    ///
    /// @return  �V�F�[�_�[���[�_�[�̃A�h���X
    ///
    virtual IShaderLoader* getShaderLoader() const = 0;
    ///
    /// @brief   �e�N�X�`�����[�_�[�̎擾
    ///
    /// @return  �e�N�X�`�����[�_�[�̃A�h���X
    ///
    virtual ITextureLoader* getTextureLoader() const = 0;

protected :
    virtual ~IPlatform() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_HEADER_
/// EOF
