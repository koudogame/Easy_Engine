///
/// @file   shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHAPE_HEADER_
#define INCLUDED_EGEG_SHAPE_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct Shape
/// @brief  �`�\���̃x�[�X
///
struct Shape
{
    Vector2D position;      ///< ���W
    float    rotation_rad;  ///< ��]�p(rad.)

    virtual ~Shape() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHAPE_HEADER_
/// EOF
