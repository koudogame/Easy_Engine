///
/// @file   line_2d.hpp
/// @author 板場
///
/// @brief  線分( 2D )
#ifndef INCLUDED_EGEG_LINE_2D_HEADER_
#define INCLUDED_EGEG_LINE_2D_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
struct Line2D
{
    Vector2D start; ///< 始点
    Vector2D end;   ///< 終点
};
END_EGEG
#endif /// !INCLUDED_EGEG_LINE_2D_HEADER_
/// EOF
