///
/// @file   circle_shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#define INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#include "shape.hpp"
#include "collision_detection.hpp"
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
    void setPosition( const Vector2D& Position ) override { shape_.origin = Position; }
    ///
    /// @brief  ���a�̐ݒ�
    ///
    /// @param[in] Radius : ���a
    ///
    void setRadius( float Radius ) { shape_.radius = Radius; }

/*-----------------------------------------------------------------*/
// Shape
    bool isCollided( const Shape* Other ) const override { return Other->isCollided( shape_ ); }
    bool isCollided( const Rectangle& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
    bool isCollided( const Circle& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
    bool isCollided( const Line& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
/*-----------------------------------------------------------------*/
private :
    Circle shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
/// EOF
