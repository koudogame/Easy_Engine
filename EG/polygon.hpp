#ifndef INCLUDED_EG_EG_POLYGON_HEADER_
#define INCLUDED_EG_EG_POLYGON_HEADER_
// �쐬�� : ��
#include <vector>
#include "vertex_data.hpp"

BEGIN_EG_EG
//
// �|���S���f�[�^
//
struct Polygon
{
    std::vector<VertexData> vertices;
};
END_EG_EG
#endif
// EOF
