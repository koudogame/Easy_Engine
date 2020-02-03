///
/// @file   line.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LINE_HEADER_
#define INCLUDED_EGEG_LINE_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct Line
/// @brief  線分
///
struct Line
{
    Vector2D start; ///< 始点
    Vector2D line;  ///< 方向と大きさを示すベクトル
};
END_EGEG
#endif /// !INCLUDED_EGEG_LINE_HEADER_
/// EOF
