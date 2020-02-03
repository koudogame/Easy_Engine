///
/// @file   line_shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LINE_SHAPE_HEADER_
#define INCLUDED_EGEG_LINE_SHAPE_HEADER_
#include "shape.hpp"
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
    void setPosition( const Vector2D& Position ) { shape_.start = Position; }
    ///
    /// @brief  �����̃Z�b�g
    ///
    /// @param[in] Vector : ������\���x�N�g��
    ///
    void setVector( const Vector2D& Vector ) { shape_.vector = Vector; }

/*-----------------------------------------------------------------*/
// Shape
    bool isCollision( Shape* Other ) const override { return Other->isCollision( shape_ ); }
    bool isCollision( const Rectangle& ) const override;
    bool isCollision( const Circle& ) const override;
    bool isCollision( const Line& ) const override;
/*-----------------------------------------------------------------*/
private :
    Line shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_LINE_SHAPE_HEADER_
/// EOF
