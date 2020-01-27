///
/// @file   renderer.hpp
/// @author ��
///
/// @brief  �����_���[
///
#ifndef INCLUDED_EGEG_RENDERER_HEADER_
#define INCLUDED_EGEG_RENDERER_HEADER_
#include "model.hpp"
BEGIN_EGEG
class IRenderer
{
public :
    ///
    /// @enum   BlendMode
    /// @brief  �������[�h
    ///
    enum BlendMode
    {
        kNormal,        ///< �ʏ탂�[�h *�`��F�����̂܂ܕ`��
        kAdditive,      ///< ���Z���[�h *���̐F�ƕ`��F�����Z�����F��`��
        kSubtraction,   ///< ���Z���[�h *���̐F����`��F�����Z�����F��`��
    };

    ///
    /// @brief  �`��Ώۉ�ʂ̃T�C�Y�擾
    ///
    /// @return �`��Ώۉ�ʃT�C�Y
    ///
    virtual Vector2D getScreenSize() const = 0;

    ///
    /// @brief  ��ʃN���A
    /// @details �����̃J���[���́A�e�F0.0F ~ 1.0F�Őݒ肵�Ă��������B
    ///
    /// @param[in] ColorRGBA : �N���A�F { R, G, B, A }
    ///
    virtual void clear( const Vector4D& ColorRGBA ) = 0;

    ///
    /// @brief  �`��J�n
    ///
    virtual void beginRender() = 0;

    ///
    /// @brief  ���f���̕`��
    ///
    /// @param[in] Model : �`�悷�郂�f��
    /// @param[in] Mode  : �`�惂�[�h
    ///
    virtual void renderModel( const Model& Model, BlendMode Mode = BlendMode::kNormal ) = 0;

    ///
    /// @brief  �`��I��
    ///
    virtual void endRender() = 0;


    virtual ~IRenderer() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_HEADER_
/// EOF
