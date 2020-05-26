///
/// @file   mesh.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_

#include <memory>
#include <vector>
#include "shader.hpp"
#include "vertex.hpp"
#include "material.hpp"

BEGIN_EGEG

///
/// @struct SubMesh
/// @brief  サブメッシュ
///
struct SubMesh
{
    IShader* shader;
    Material material;
    size_t num_vertices = 0U;
    size_t start_index  = 0U;
    size_t base_vertex  = 0U;
};


///
/// @struct Mesh
/// @brief  メッシュ
///
struct Mesh
{
    Vertex vertices;
    std::vector<SubMesh> sub_mesh_list;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
