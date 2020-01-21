///
/// @file    sprite.hpp
/// @author  ��
///          
/// @brief   �X�v���C�g
/// @details 2D�e�N�X�`���̕`����s���܂��B
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_
#include "rendering_manager.hpp"
BEGIN_EGEG
class Sprite
{
public :
    ///
    /// @brief  ����������
    ///
    /// @param[in] TextureFileName : �ǂݍ��ރe�N�X�`���̃t�@�C��(�p�X)��
    ///
    /// @return ����������[ true ] ���������s[ false ]
    ///
    bool initialize( const std::wstring& TextureFileName );
    ///
    /// @brief  �I������
    ///
    void finalize();

    ///
    /// @brief  �摜�̕`��
    ///
    /// @param[in] Position : �\�����W
    /// @param[in] Trimming : �摜�؂���͈�
    /// @param[in] Alpha    : �\�����l *0.0F ~ 1.0F�̊�*
    /// @param[in] Rotation : ��]�p�x( �x���@ )
    /// @param[in] Scale    : �g�嗦
    /// @param[in] Origin   : ���_ *���ォ��̑��Έʒu*
    ///
    void draw(
        const Vector2D& Position,
        const Vector4D& Trimming,
        float Alpha = 1.0F,
        float Rotation = 0.0F,
        const Vector2D& Scale = { 1.0F, 1.0F },
        const Vector2D& Origin = { 0.0F, 0.0F }
    );

private :
    ITexture* texture_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
