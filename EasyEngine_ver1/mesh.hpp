///
/// @file    mesh.hpp
/// @author  ��
///
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_
#include <vector>
#include "vertex_data.hpp"
#include "vertex_index.hpp"
BEGIN_EGEG
///
/// @struct Mesh
///          
/// @brief   ���b�V��
/// @details �C���f�b�N�X�́A���_�f�[�^�ɑ΂���C���f�b�N�X�ł��B<br>
///          ���ɐ����`���`�����������܂��B( ���_xy���W�̂� )<br>
///          ex.) Vertices { {-0.5F, 0.5F}, {-0.5F, -0.5F}, {0.5F, 0.5F}, {-0.5F, -0.5F} }<br>
///               Indices  { {0, 1, 2}, {1, 3, 2} }
///
struct Mesh
{
    std::vector<Mesh> vertices;   ///< ���_�f�[�^
    std::vector<VertexIndex> indices;   ///< ���_�̃C���f�b�N�X
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
