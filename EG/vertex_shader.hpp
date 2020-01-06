#ifndef INCLUDED_EG_EG_VERTEX_SHADER_HEADER
#define INCLUDED_EG_EG_VERTEX_SHADER_HEADER
// 作成者 : 板場
#include "easy_engine.hpp"

BEGIN_EG_EG
//
// 頂点シェーダー
//
class IVertexShader
{
public:
    virtual ~IVertexShader() = default;

    virtual void release() = 0;
};
END_EG_EG
#endif
// EOF
