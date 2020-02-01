///
/// @file   collision_detection.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COLLISION_DETECTION_HEADER_
#define INCLUDED_EGEG_COLLISION_DETECTION_HEADER_
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"
BEGIN_EGEG
///
/// @class  CollisionDetection
/// @brief  衝突判定クラス
///
class CollisionDetection
{
public :
    ///
    /// @brief  矩形と矩形の衝突判定
    ///
    /// @param[in] Rect1 : 矩形1
    /// @param[in] Rect2 : 矩形2
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    static bool isCollided( const Rectangle& Rect1, const Rectangle& Rect2 );
    ///
    /// @brief  円形と円形の衝突判定
    ///
    /// @param[in] Circle1 : 円形1
    /// @param[in] Circle2 : 円形2
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    static bool isCollided( const Circle& Circle1, const Circle& Circle2 );
    ///
    /// @brief  線分と線分の交差判定
    ///
    /// @param[in]  Line1 : 線分１
    /// @param[in]  Line2 : 線分2
    /// @param[out] DivRatio1 : Line1に対する内分比
    /// @param[out] DivRatio2 : Line2に対する内分比
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    static bool isCollided( const Line& Line1, const Line& Line2, float* DivRatio1 = nullptr, float* DivRatio2 = nullptr );
    ///
    /// @brief  矩形と円形の衝突判定
    ///
    /// @param[in] Rect   : 矩形
    /// @param[in] Circle : 円形
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    static bool isCollided( const Rectangle& Rect, const Circle& Circle );
    static bool isCollided( const Circle& Circle, const Rectangle& Rect ) { return isCollided( Rect, Circle ); }
    ///
    /// @brief  矩形と線分の衝突判定
    ///
    /// @param[in] Rect : 矩形
    /// @param[in] Line : 線分
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    static bool isCollided( const Rectangle& Rect, const Line& Line );
    static bool isCollided( const Line& Line, const Rectangle& Rect ) { return isCollided( Rect, Line ); }
    ///
    /// @brief  円形と線分の衝突判定
    ///
    /// @param[in] Circle : 円形
    /// @param[in] Line   : 線分
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    static bool isCollided( const Circle& Circle, const Line& Line );
    static bool isCollided( const Line& Line, const Circle& Circle ) { return isCollided( Circle, Line );  }
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_DETECTION_HEADER_
/// EOF
