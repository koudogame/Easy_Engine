///
/// @file   rectangle_shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
#define INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
#include "shape.hpp"
#include "collision_detection.hpp"
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
    void setPosition( const Vector2D& Position ) override { shape_.origin = Position; }
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
    bool isCollided( const Shape* Other ) const override { return Other->isCollided( shape_ ); }
    bool isCollided( const Rectangle& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
    bool isCollided( const Circle& Other ) const override { return CollisionDetection::isCollided( shape_, Other ); }
    bool isCollided( const Line& Other ) const override { return CollisionDetection::isCollided( shape_,Other ); }
/*-----------------------------------------------------------------*/
private :
    Rectangle shape_ = {};
};
END_EGEG
#endif /// !INCLUDED_EGEG_RECTANGLE_SHAPE_HEADER_
/// EOF
