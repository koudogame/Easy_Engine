///
/// @file   line.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LINE_HEADER_
#define INCLUDED_EGEG_LINE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @struct Line
/// @brief  線分
///
struct Line :
    public Shape
{
    Vector2D start; ///< 始点
    Vector2D end;   ///< 終点
};
END_EGEG
#endif /// !INCLUDED_EGEG_LINE_HEADER_
/// EOF
