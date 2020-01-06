#ifndef INCLUDED_EG_EG_VERTEX_DATA_HEADER_
#define INCLUDED_EG_EG_VERTEX_DATA_HEADER_
// 作成者 : 板場
#include "eg_math.hpp"

BEGIN_EG_EG
//
// 頂点データ構造体
//
struct VertexData
{
    Float3 position;
    Float2 uv;
    Float4 color;
};
END_EG_EG
#endif // INCLUDED_EG_EG_VERTEX_DATA_HEADER_
// EOF
