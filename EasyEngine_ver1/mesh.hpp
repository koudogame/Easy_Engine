///
/// @file    mesh.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_
#include <vector>
#include "vertex_data.hpp"
#include "vertex_index.hpp"
BEGIN_EGEG
///
/// @struct Mesh
///          
/// @brief   メッシュ
/// @details インデックスは、頂点データに対するインデックスです。<br>
///          下に正方形を定義する例を示します。( 頂点xy座標のみ )<br>
///          ex.) Vertices { {-0.5F, 0.5F}, {-0.5F, -0.5F}, {0.5F, 0.5F}, {-0.5F, -0.5F} }<br>
///               Indices  { {0, 1, 2}, {1, 3, 2} }
///
struct Mesh
{
    std::vector<Mesh> vertices;   ///< 頂点データ
    std::vector<VertexIndex> indices;   ///< 頂点のインデックス
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
