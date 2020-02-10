///
/// @file   line_shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LINE_SHAPE_HEADER_
#define INCLUDED_EGEG_LINE_SHAPE_HEADER_
#include "shape.hpp"
#include "collision_detection.hpp"
BEGIN_EGEG
///
/// @class  LineShape
/// @brief  �Փ˔���@�\�t������
///
class LineShape :
    public Shape
{
public :
    ///
    /// @brief  �X�e�[�^�X�̐ݒ�
    ///
    /// @param[in] Position : ���W
    /// @param[in] Vector   : ������\���x�N�g��
    ///
    void setStatus( const Vector2D& Position, const Vector2D& Vector ) { setPosition( Position ); setVector( Vector ); }
    ///
    /// @brief  ���W�̃Z�b�g
    ///
    /// @param[in] Position : ���W
    ///
    void setPosition( const Vector2D& Position ) override { shape_.start = Position; }
    ///
    /// @brief  �����̃Z�b�g
    ///
    /// @param[in] Vector : ������\���x�N�g��
    ///
    void setVector( const Vector2D& Vector ) { shape_.line = Vector; }

/*-----------------------------------------------------------------*/
// Shape
    bool isCollided( const Shape* Other ) const override { return Other->isCollided( shape_ ); }
    bool isCollided( const Rectangle& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
    bool isCollided( const Circle& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
    bool isCollided( const Line& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
/*-----------------------------------------------------------------*/
private :
    Line shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_LINE_SHAPE_HEADER_
/// EOF
