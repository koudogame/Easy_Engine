///
/// @file   cuboid.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CUBOID_HEADER_
#define INCLUDED_EGEG_CUBOID_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct Cuboid
/// @brief  直方体
///
struct Cuboid
{
    Vector3D center;    ///< 中心点
    float    width;     ///< 横幅
    float    height;    ///< 高さ
    float    depth;     ///< 奥行き
};
END_EGEG
#endif /// !INCLUDED_EGEG_CUBOID_HEADER_
/// EOF
