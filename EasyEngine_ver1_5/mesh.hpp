///
/// @file   mesh.hpp
/// @author î¬èÍ
/// 
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_

#include <memory>
#include <vector>
#include "property.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "material.hpp"

BEGIN_EGEG

using Mesh = Property<
        Tag<Vertex>,
        Tag<Material>,
        Tag<IShader*>,
        Tag<size_t>>;

END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
