///
/// @file   mesh.hpp
/// @author 板場
///
/// @brief  メッシュ構造体
///
#ifndef INCLUDED_EG_EG_MESH_HEADER_
#define INCLUDED_EG_EG_MESH_HEADER_
#include <vector>
#include "face.hpp"
BEGIN_EGEG
struct Mesh
{
    std::vector<Face> faces_;   ///< フェース
};
END_EGEG
#endif /// INCLUDED_EG_EG_MESH_HEADER_
/// EOF
