///
/// @file   circle_shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#define INCLUDED_EGEG_CIRCLE_SHAPE_HEADER_
#include "shape.hpp"
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
    void setPosition( const Vector2D& Position ) { shape_.origin = Position; }
    ///
    /// @brief  半径の設定
    ///
    /// @param[in] Radius : 半径
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
