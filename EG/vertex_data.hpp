///
/// @file   vertex_data.hpp
/// @author ��
///
/// @brief  ���_�f�[�^�\����
///
#ifndef INCLUDED_EG_EG_VERTEX_DATA_HEADER_
#define INCLUDED_EG_EG_VERTEX_DATA_HEADER_
#include "eg_math.hpp"
BEGIN_EG_EG
struct VertexData
{
    Float3 position;    ///< ���_���W
    Float2 uv;          ///< ���_UV���W
    Float4 color;       ///< ���_�F
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_VERTEX_DATA_HEADER_
/// EOF
