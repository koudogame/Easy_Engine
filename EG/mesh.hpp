#ifndef INCLUDED_EG_EG_MESH_HEADER_
#define INCLUDED_EG_EG_MESH_HEADER_
// �쐬�� : ��
#include <vector>
#include "polygon.hpp"

BEGIN_EG_EG
//
// ���b�V���\����
//
struct Mesh
{
    std::vector<Polygon> faces;
};
END_EG_EG
#endif // INCLUDED_EG_EG_MESH_HEADER_
// EOF
