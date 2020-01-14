///
/// @file   vertex_data.hpp
/// @author 板場
///
/// @brief  頂点データ
///
#ifndef INCLUDED_EGEG_VERTEX_DATA_HEADER_
#define INCLUDED_EGEG_VERTEX_DATA_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
struct VertexData
{
    Vector3D position;
    Vector2D uv;
    Vector4D color_rgba;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_DATA_HEADER_
/// EOF
