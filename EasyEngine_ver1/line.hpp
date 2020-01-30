///
/// @file   line.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LINE_HEADER_
#define INCLUDED_EGEG_LINE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @struct Line
/// @brief  ����
///
struct Line :
    public Shape
{
    Vector2D start; ///< �n�_
    Vector2D end;   ///< �I�_
};
END_EGEG
#endif /// !INCLUDED_EGEG_LINE_HEADER_
/// EOF
