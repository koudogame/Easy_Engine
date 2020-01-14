///
/// @file   renderer.hpp
/// @author ��
///
/// @brief  �����_���[
///
#ifndef INCLUDED_EGEG_RENDERER_HEADER_
#define INCLUDED_EGEG_RENDERER_HEADER_
#include "interface.hpp"
#include "model.hpp"
BEGIN_EGEG
class IRenderer :
    public Interface
{
public :
    ///
    /// @brief   �`��J�n
    /// @details �����̃J���[���́A�e�F0.0F ~ 1.0F�Őݒ肵�Ă��������B
    ///
    /// @param[in] ColorRGBA : ��ʂ̃N���A�F { R, G, B, A }
    ///
    virtual void beginRender( const Vector4D& Color ) = 0;
    ///
    /// @brief   �`��̃G���g���[
    /// @details ���ۂɕ`��͍s���܂���B
    ///
    /// @param[in] Model : �`�悷�郂�f��
    ///
    virtual void entryRender( const Model& Model ) = 0;
    ///
    /// @brief   �`��I��
    /// @details beginRender�̌Ăяo������A<br>
    ///          ���̊֐����Ăяo�����܂łɃG���g���[���ꂽ���f����`�悵�܂��B
    ///
    virtual void endRender() = 0;

protected :
    virtual ~IRenderer() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_HEADER_
/// EOF
