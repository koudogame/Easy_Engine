///
/// @file   platform.hpp
/// @author ��
///
/// @brief  �v���b�g�t�H�[��
///
#ifndef INCLUDED_EGEG_PLATFORM_HEADER_
#define INCLUDED_EGEG_PLATFORM_HEADER_
#include <functional>
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class IPlatform
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
    virtual void mainLoop( std::function<bool(uint64_t)> pUpdateFunction ) = 0;

    ///
    /// @brief  �_�C�A���O�{�b�N�X�̕\��
    ///
    /// @param[in] Message : �_�C�A���O�{�b�N�X�ɕ\�����镶����
    ///
    virtual void showDialogBox( const std::string& Message ) = 0;

    ///
    /// @brief   �����_���[�̐���
    ///
    /// @param[out] ppRenderer : �������������_���[���i�[����C���^�[�t�F�C�X
    ///
    /// @return �����ɐ���[ true ] �����Ɏ��s[ false ]
    ///
    virtual bool createRenderer( IRenderer** ppRenderer ) = 0;
    ///
    /// @brief   �V�F�[�_�[���[�_�[�̐���
    ///    
    /// @param[out] ppShaderLoader : ���������V�F�[�_�[���[�_�[���i�[����C���^�[�t�F�C�X
    ///
    /// @return �����ɐ���[ true ] �����Ɏ��s[ false ]
    ///
    virtual bool createShaderLoader( IShaderLoader** ppShaderLoader ) = 0;
    ///
    /// @brief   �e�N�X�`�����[�_�[�̐���
    ///
    /// @param[out] ppTextureLoader : ���������e�N�X�`�����[�_�[���i�[����C���^�[�t�F�C�X
    ///
    /// @return �����ɐ���[ true ] �����Ɏ��s[ false ]
    ///
    virtual bool createTextureLoader( ITextureLoader** ppTextureLoader ) = 0;

    virtual ~IPlatform() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_HEADER_
/// EOF
