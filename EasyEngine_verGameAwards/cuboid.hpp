///
/// @file   cuboid.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CUBOID_HEADER_
#define INCLUDED_EGEG_CUBOID_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct Cuboid
/// @brief  ������
///
struct Cuboid
{
    Vector3D center;    ///< ���S�_
    float    width;     ///< ����
    float    height;    ///< ����
    float    depth;     ///< ���s��
};
END_EGEG
#endif /// !INCLUDED_EGEG_CUBOID_HEADER_
/// EOF
