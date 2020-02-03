///
/// @file   rectangle_shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
#define INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @class  RectangleShape
/// @brief  衝突判定機能付き矩形
///
class RectangleShape :
    public Shape
{
public :
    ///
    /// @brief  ステータスの設定
    ///
    /// @param[in] Position : 座標
    /// @param[in] Width    : 横幅
    /// @param[in] Height   : 縦幅
    ///
    void setStatus( const Vector2D& Position, float Width, float Height ) { setPosition( Position ); setWidth( Width ); setHeight( Height ); }
    ///
    /// @brief  座標の設定
    ///
    /// @param[in] Position : 座標
    ///
    void setPosition( const Vector2D& Position ) { shape_.origin = Position; }
    ///
    /// @brief  横幅の設定
    ///
    /// @param[in] Width : 横幅
    ///
    void setWidth( float Width ) { shape_.width = Width; }
    ///
    /// @brief  縦幅の設定
    ///
    /// @param[in] Height :  縦幅
    ///
    void setHeight( float Height ) { shape_.height = Height; }

/*-----------------------------------------------------------------*/
// Shape
    bool isCollision( Shape* Other ) const override { return Other->isCollision( shape_ ); }
    bool isCollision( const Rectangle& ) const override;
    bool isCollision( const Circle& ) const override;
    bool isCollision( const Line& ) const override;
/*-----------------------------------------------------------------*/
private :
    Rectangle shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
/// EOF
