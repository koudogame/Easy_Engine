///
/// @file   mesh.hpp
/// @author ��
///
/// @brief  ���b�V���\����
///
#ifndef INCLUDED_EG_EG_MESH_HEADER_
#define INCLUDED_EG_EG_MESH_HEADER_
#include <vector>
#include "face.hpp"
BEGIN_EGEG
struct Mesh
{
    std::vector<Face> faces_;   ///< �t�F�[�X
};
END_EGEG
#endif /// INCLUDED_EG_EG_MESH_HEADER_
/// EOF
