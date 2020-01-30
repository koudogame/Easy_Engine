///
/// @file   shape.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHAPE_HEADER_
#define INCLUDED_EGEG_SHAPE_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct Shape
/// @brief  形構造体ベース
///
struct Shape
{
    Vector2D position;      ///< 座標
    float    rotation_rad;  ///< 回転角(rad.)

    virtual ~Shape() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHAPE_HEADER_
/// EOF
