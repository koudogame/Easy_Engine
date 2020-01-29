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
    SpriteComponent( Actor* Owner );

    ///
    /// @brief  �X�v���C�g���̃Z�b�g
    ///
    /// @param[in] pTexture    : �e�N�X�`��
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
    /// @brief  �e�N�X�`���̃Z�b�g
    ///
    /// @param[in] pTexture : �e�N�X�`��
    ///
    void setTexture( ITexture* pTexture );
    ///
    /// @brief  �`����W�̃Z�b�g
    ///
    /// @param[in] Position : ���W
    ///
    void setPosition( const Vector2D& Position ) { position_ = Position; }
    ///
    /// @brief  �e�N�X�`���؂���͈͂̃Z�b�g
    ///
    /// @param[in] Trimming : �؂���͈�
    ///
    void setTrimming( const Vector4D& Trimming ) { trimming_ = Trimming; }
    ///
    /// @brief   �]�p�̃Z�b�g
    ///
    void setRotation( float RotationDEG ) { rotation_ = RotationDEG; }
    ///
    /// @brief  �g�k���̃Z�b�g
    ///
    /// @param[in] Scale : �g�k��
    ///
    void setScale( const Vector2D& Scale ) { scale_ = Scale; }
    ///
    /// @brief   ���_�̃Z�b�g
    /// @details { 0.0F, 0.0F }���摜�̍���Ƃ����Ƃ��̑��΍��W�ł��B
    ///
    /// @param[in] Origin : ���_
    ///
    void setOrigin( const Vector2D& Origin ) { origin_ = Origin; }
    ///
    /// @brief   �J���[�̃Z�b�g
    /// @details �e�F 0.0F ~ 1.0F �͈͓̔��Őݒ肵�ĉ������B
    ///
    /// @param[in] Color : �F{ R, G, B }
    ///
    void setColor( const Vector3D& Color ) { color_.x = Color.x; color_.y = Color.y; color_.z = Color.z; }
    ///
    /// @brief   �J���[�̃Z�b�g
    /// @details �e�F 0.0F ~ 1.0F �͈̔͂Őݒ肵�ĉ������B
    ///
    /// @param[in] Color : �F{ R, G, B, A }
    ///
    void setColor( const Vector4D& Color ) { color_ = Color; }
    ///
    /// @brief  �A���t�@�l�̃Z�b�g
    ///
    /// @param[in] Alpha : �A���t�@�l( 0.0F ~ 1.0F )
    ///
    void setAlpha( float Alpha ) { color_.w = Alpha; }
    ///
    /// @brief  �[�x�l�̃Z�b�g
    ///
    /// @param[in] Depth : �[�x�l( 0.0F ~ 1.0F )
    ///
    void setDepth( float Depth ) { depth_ = Depth; }
        
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize() override;
/*-----------------------------------------------------------------*/
private :
/*-----------------------------------------------------------------*/
// RenderComponent
    void render() override;             /// �ʏ�RenderBatch�ȊO����̌Ăяo�����֎~���Ă��܂��B
/*-----------------------------------------------------------------*/
    void getModelStatus( Model* );
    void getVerticesPositoin( Vector3D* );
    void getVerticesUV( Vector2D* );

    bool  is_validity_ = false;         /// �L����Ԕ���t���O
    ITexture* p_texture_ = nullptr;     /// �e�N�X�`��
    Vector2D  position_;                /// �`����W
    Vector4D  trimming_;                /// �e�N�X�`���؂���͈�
    float     rotation_;                /// ��]�p(�x���@)
    Vector2D  scale_;                   /// �g�k��
    Vector2D  origin_;                  /// ���_
    Vector4D  color_;                   /// �F���
    float     depth_;                   /// �[�x�l
    IVertexShader* p_vertex_shader_;    /// ���_�V�F�[�_�\
    IPixelShader*  p_pixel_shader_;     /// �s�N�Z���V�F�[�_�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
