///
/// @file   rectangle.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_RECTANGLE_HEADER_
#define INCLUDED_EGEG_RECTANGLE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @struct Rectangle
/// @brief  ãÈå`
///
struct Rectangle :
    public Shape
{
    float width;    ///< â°ïù
    float height;   ///< çÇÇ≥
};
END_EGEG
#endif /// !INCLUDED_EGEG_RECTANGLE_HEADER_
/// EOF
