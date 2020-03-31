///
/// @file    vertex_index.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_VERTEX_INDEX_HEADER_
#define INCLUDED_EGEG_VERTEX_INDEX_HEADER_
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @struct VertexIndex
///          
/// @brief   頂点インデックス
/// @details 3角形ポリゴンを形成する頂点のインデックスを保持します。
///
struct VertexIndex
{
    unsigned index_for_buffer[3];
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_INDEX_HEADER_
/// EOF
