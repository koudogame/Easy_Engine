///
/// @file   rectangle.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RECTANGLE_HEADER_
#define INCLUDED_EGEG_RECTANGLE_HEADER_
#include "shape.hpp"
BEGIN_EGEG
///
/// @struct Rectangle
/// @brief  ��`
///
struct Rectangle :
    public Shape
{
    float width;    ///< ����
    float height;   ///< ����
};
END_EGEG
#endif /// !INCLUDED_EGEG_RECTANGLE_HEADER_
/// EOF
