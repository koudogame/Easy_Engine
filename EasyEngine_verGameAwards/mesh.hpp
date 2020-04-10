///
/// @file   mesh.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_

#include <DirectXMath.h>
#include "vertex.hpp"
#include "sub_mesh.hpp"

BEGIN_EGEG

struct Mesh
{
    Vertex vertices;
    std::vector<SubMesh> submesh_list;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
