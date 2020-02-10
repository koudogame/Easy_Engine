///
/// @file   circle_shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#define INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#include "shape.hpp"
#include "collision_detection.hpp"
BEGIN_EGEG
///
/// @class  CircleShape
/// @brief  衝突判定機能付き円形
/// 
class CircleShape :
    public Shape
{
public :
    ///
    /// @brief  ステータスの設定
    ///
    /// @param[in] Position : 座標
    /// @param[in] Radius   : 半径
    ///
    void setStatus( const Vector2D& Position, float Radius ) { setPosition( Position ); setRadius( Radius ); }
    ///
    /// @brief  座標の設定
    ///
    /// @param[in] Position : 座標
    ///
    void setPosition( const Vector2D& Position ) override { shape_.origin = Position; }
    ///
    /// @brief  半径の設定
    ///
    /// @param[in] Radius : 半径
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
