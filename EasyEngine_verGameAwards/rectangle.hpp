///
/// @file   rectangle.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RECTANGLE_HEADER_
#define INCLUDED_EGEG_RECTANGLE_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct Rectangle
/// @brief  長方形
///
struct Rectangle
{
    Vector2D center;    ///< 中心点
    float    width;     ///< 横幅
    float    height;    ///< 高さ
};
END_EGEG
#endif /// !INCLUDED_EGEG_RECTANGLE_HEADER_
/// EOF
