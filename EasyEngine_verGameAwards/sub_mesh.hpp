///
/// @file   sub_mesh.hpp
/// @author ��
///
#ifndef INCLUDED_EG_EG_SUB_MESH_HEADER_
#define INCLUDED_EG_EG_SUB_MESH_HEADER_

#include <d3d11.h>
#include "table.hpp"
#include "material.hpp"

BEGIN_EGEG

///
/// @struct SubMesh
/// @brief  �T�u���b�V��
///
struct SubMesh
{
    Material material;
    uint32_t start_index;
    uint32_t num_vertices;
};

END_EGEG
#endif /// !INCLUDED_EG_EG_SUB_MESH_HEADER_
/// EOF
