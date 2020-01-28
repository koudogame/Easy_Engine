///
/// @file   sprite.hpp
/// @author ��
///
/// @brief  �X�v���C�g�R���|�[�l���g
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_
#include "render_component.hpp"
#include "egeg_math.hpp"
#include "texture.hpp"
#include "model.hpp"
BEGIN_EGEG
class SpriteComponent :
    public RenderComponent
{
public :
    SpriteComponent();

    ///
    /// @brief  �X�v���C�g���̃Z�b�g
    ///
    /// @param[in] pTexture    : �`�悷��e�N�X�`��
    /// @param[in] Position    : �`��ʒu
    /// @param[in] Trimming    : �e�N�X�`���؂���͈�
    /// @param[in] RotationDEG : ��]�p�x( �x���@ )
    /// @param[in] Scale       : �g�k��( x,y�e 0.0F ~ 1.0F )
    /// @param[in] Origin      : ���_
    /// @param[in] Color       : �J���[�l
    /// @param[in] Alpha       : �A���t�@�l
    /// @param[in] Depth       : �[�x�l( 0.0F ~ 1.0F )
    ///
    void setStatus( ITexture* pTexture,
                    const Vector2D& Position,
                    const Vector4D& Trimming,
                    float RotationDEG = 0.0F,
                    const Vector2D& Scale = Vector2D{ 1.0F, 1.0F },
                    const Vector2D& Origin = Vector2D{ 0.0F, 0.0F },
                    const Vector3D& Color = Vector3D{ 0.0F, 0.0F, 0.0F },
                    float Alpha = 1.0F,
                    float Depth = 0.0F );

    ///
    /// @brief  �`����s�����ǂ����̐ݒ�
    ///
    /// @param[in] Visible : �`�悷��[ true ] �`�悵�Ȃ�[ false ]
    ///
    void setVisible( bool Visible ) { visible_ = Visible; }

// RenderComponent
/*-----------------------------------------------------------------*/
    void render() override;

// IComponent
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

private :
    bool  validity_ = false;    /// �L����Ԃ�
    bool  visible_ = false;     /// ����Ԃ�
    Model sprite_;              /// ���f�����
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
