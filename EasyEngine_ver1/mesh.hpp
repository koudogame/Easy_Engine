///
/// @file    mesh.hpp
/// @author  板場
///          
/// @brief   メッシュ
/// @details インデックスは、頂点データに対するインデックスです。<br>
///          下に正方形を定義する例を示します。( 頂点xy座標のみ )<br>
///          ex.) Vertices { {-0.5F, 0.5F}, {-0.5F, -0.5F}, {0.5F, 0.5F}, {-0.5F, -0.5F} }<br>
///               Indices  { {0, 1, 2}, {1, 3, 2} }
///
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_
#include <vector>
#include "vertex_data.hpp"
BEGIN_EGEG
struct Mesh
{
    std::vector<VertexData> vertices;   ///< 頂点データ
    std::vector<unsigned[3]> indices;   ///< 頂点のインデックス
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
