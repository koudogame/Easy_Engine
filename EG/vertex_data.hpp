///
/// @file   vertex_data.hpp
/// @author 板場
///
/// @brief  頂点データ構造体
///
#ifndef INCLUDED_EG_EG_VERTEX_DATA_HEADER_
#define INCLUDED_EG_EG_VERTEX_DATA_HEADER_
#include "eg_math.hpp"
BEGIN_EG_EG
struct VertexData
{
    Float3 position;    ///< 頂点座標
    Float2 uv;          ///< 頂点UV座標
    Float4 color;       ///< 頂点色
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_VERTEX_DATA_HEADER_
/// EOF
