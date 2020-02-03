///
/// @file   line_shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LINE_SHAPE_HEADER_
#define INCLUDED_EGEG_LINE_SHAPE_HEADER_
#include "shape.hpp"
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
    void setPosition( const Vector2D& Position ) { shape_.start = Position; }
    ///
    /// @brief  線分のセット
    ///
    /// @param[in] Vector : 線分を表すベクトル
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
