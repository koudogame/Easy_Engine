#ifndef INCLUDED_EG_EG_FACE_HEADER_
#define INCLUDED_EG_EG_FACE_HEADER_
// �쐬�� : ��
#include <vector>
#include "vertex_data.hpp"

BEGIN_EG_EG
//
// �t�F�[�X�\����
//
struct Face
{
    std::vector<VertexData> vertices_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_FACE_HEADER_
// EOF
