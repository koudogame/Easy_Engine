///
/// @file    face.hpp
/// @author  ��
///          
/// @brief   �t�F�[�X�\����
///
/// @details ���_�𕡐�(��)�����܂��B
///
#ifndef INCLUDED_EG_EG_FACE_HEADER_
#define INCLUDED_EG_EG_FACE_HEADER_
#include <vector>
#include "vertex_data.hpp"
BEGIN_EG_EG
struct Face
{
    std::vector<VertexData> vertices_;  ///< ���_
};
END_EG_EG
#endif /// INCLUDED_EG_EG_FACE_HEADER_
/// EOF
