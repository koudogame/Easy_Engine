#ifndef INCLUDED_EG_EG_MESH_HEADER_
#define INCLUDED_EG_EG_MESH_HEADER_
// 作成者 : 板場
#include <vector>
#include "face.hpp"

BEGIN_EG_EG
//
// メッシュ構造体
//
struct Mesh
{
    std::vector<Face> faces_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_MESH_HEADER_
// EOF
