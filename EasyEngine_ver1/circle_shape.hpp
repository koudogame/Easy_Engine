///
/// @file   circle_shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#define INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @class  CircleShape
/// @brief  �Փ˔���@�\�t���~�`
/// 
class CircleShape :
    public Shape
{
public :
    ///
    /// @brief  �X�e�[�^�X�̐ݒ�
    ///
    /// @param[in] Position : ���W
    /// @param[in] Radius   : ���a
    ///
    void setStatus( const Vector2D& Position, float Radius ) { setPosition( Position ); setRadius( Radius ); }
    ///
    /// @brief  ���W�̐ݒ�
    ///
    /// @param[in] Position : ���W
    ///
    void setPosition( const Vector2D& Position ) { shape_.origin = Position; }
    ///
    /// @brief  ���a�̐ݒ�
    ///
    /// @param[in] Radius : ���a
    ///
    void setRadius( float Radius ) { shape_.radius = Radius; }

/*-----------------------------------------------------------------*/
// Shape
    bool isCollision( Shape* Other ) const override { return Other->isCollision( shape_ ); }
    bool isCollision( const Rectangle& ) const override;
    bool isCollision( const Circle& ) const override;
    bool isCollision( const Line& ) const override;
/*-----------------------------------------------------------------*/
private :
    Circle shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
/// EOF
