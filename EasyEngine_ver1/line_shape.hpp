///
/// @file   line_shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LINE_SHAPE_HEADER_
#define INCLUDED_EGEG_LINE_SHAPE_HEADER_
#include "shape.hpp"
#include "collision_detection.hpp"
BEGIN_EGEG
///
/// @class  LineShape
/// @brief  衝突判定機能付き線分
///
class LineShape :
    public Shape
{
public :
    ///
    /// @brief  ステータスの設定
    ///
    /// @param[in] Position : 座標
    /// @param[in] Vector   : 線分を表すベクトル
    ///
    void setStatus( const Vector2D& Position, const Vector2D& Vector ) { setPosition( Position ); setVector( Vector ); }
    ///
    /// @brief  座標のセット
    ///
    /// @param[in] Position : 座標
    ///
    void setPosition( const Vector2D& Position ) override { shape_.start = Position; }
    ///
    /// @brief  線分のセット
    ///
    /// @param[in] Vector : 線分を表すベクトル
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
