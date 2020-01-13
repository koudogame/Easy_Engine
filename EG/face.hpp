///
/// @file    face.hpp
/// @author  板場
///          
/// @brief   フェース構造体
///
/// @details 頂点を複数(可変)個持ちます。
///
#ifndef INCLUDED_EG_EG_FACE_HEADER_
#define INCLUDED_EG_EG_FACE_HEADER_
#include <vector>
#include "eg_math.hpp"
BEGIN_EGEG
struct Face
{
    std::vector<Vector3D> vertices_;  ///< 頂点
};
END_EGEG
#endif /// INCLUDED_EG_EG_FACE_HEADER_
/// EOF
