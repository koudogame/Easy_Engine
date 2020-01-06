#ifndef INCLUDED_EG_EG_MESH_HEADER_
#define INCLUDED_EG_EG_MESH_HEADER_
// ì¬Ò : ”Âê
#include <vector>
#include "face.hpp"

BEGIN_EG_EG
//
// ƒƒbƒVƒ…\‘¢‘Ì
//
struct Mesh
{
    std::vector<Face> faces_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_MESH_HEADER_
// EOF
