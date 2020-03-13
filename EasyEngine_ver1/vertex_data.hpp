///
/// @file   vertex_data.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_VERTEX_DATA_HEADER_
#define INCLUDED_EGEG_VERTEX_DATA_HEADER_
#include "egeg_math.hpp"
BEGIN_EGEG
///
/// @struct VertexData
///
/// @brief  頂点データ
///
struct VertexData
{
    //Float3 position;
    Float2 uv;
    Float4 color_rgba;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_DATA_HEADER_
/// EOF
