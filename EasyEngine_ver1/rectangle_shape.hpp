///
/// @file   rectangle_shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
#define INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @class  RectangleShape
/// @brief  �Փ˔���@�\�t����`
///
class RectangleShape :
    public Shape
{
public :
    ///
    /// @brief  �X�e�[�^�X�̐ݒ�
    ///
    /// @param[in] Position : ���W
    /// @param[in] Width    : ����
    /// @param[in] Height   : �c��
    ///
    void setStatus( const Vector2D& Position, float Width, float Height ) { setPosition( Position ); setWidth( Width ); setHeight( Height ); }
    ///
    /// @brief  ���W�̐ݒ�
    ///
    /// @param[in] Position : ���W
    ///
    void setPosition( const Vector2D& Position ) override { shape_.origin = Position; }
    ///
    /// @brief  �����̐ݒ�
    ///
    /// @param[in] Width : ����
    ///
    void setWidth( float Width ) { shape_.width = Width; }
    ///
    /// @brief  �c���̐ݒ�
    ///
    /// @param[in] Height :  �c��
    ///
    void setHeight( float Height ) { shape_.height = Height; }

/*-----------------------------------------------------------------*/
// Shape
    bool isCollided( Shape* Other ) const override { return Other->isCollided( shape_ ); }
    bool isCollided( const Rectangle& ) const override;
    bool isCollided( const Circle& ) const override;
    bool isCollided( const Line& ) const override;
/*-----------------------------------------------------------------*/
private :
    Rectangle shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
/// EOF
