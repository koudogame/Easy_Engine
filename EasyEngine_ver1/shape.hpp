///
/// @file   shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHAPE_HEADER_
#define INCLUDED_EGEG_SHAPE_HEADER_
#include "egeg_math.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"
BEGIN_EGEG
///
/// @class  Shape
/// @brief  形基底クラス
///
/// @details 衝突判定を行う形クラスの基底クラスです。<br>
///          衝突判定はダブルディスパッチを利用して実装しています。
///
class Shape
{
public :
    virtual ~Shape() = default;

    ///
    /// @brief  座標の設定
    ///
    /// @param[in] Position : 座標
    ///
    virtual void setPosition( const Vector2D& Position ) = 0;

    ///
    /// @brief   衝突判定ファーストディスパッチ
    /// @details 相手の自身の形との衝突判定処理を呼び出します。
    ///
    /// @param[in] Other : 衝突を判定する相手
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Shape* Other ) const = 0;
    ///
    /// @brief  矩形との衝突判定
    ///
    /// @param[in] Rectangle : 衝突を判定する矩形
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Rectangle& Rectangle ) const = 0;
    ///
    /// @brief  円形との衝突判定
    ///
    /// @param[in] Circle : 衝突を判定する円形
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Circle& Circle ) const = 0;
    ///
    /// @brief  線分との衝突判定
    ///
    /// @param[in] Line : 衝突を判定する線分
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Line& Line ) const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHAPE_HEADER_
/// EOF
