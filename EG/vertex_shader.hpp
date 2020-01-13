///
/// @file   vertex_shader.hpp
/// @author 板場
///
/// @brief  頂点シェーダインターフェイス
///
#ifndef INCLUDED_EG_EG_VERTEX_SHADER_HEADER_
#define INCLUDED_EG_EG_VERTEX_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class IVertexShader :
    public Interface
{
public :
protected :
    virtual ~IVertexShader() = default;
};
END_EGEG
#endif /// INCLUDED_EG_EG_VERTEX_SHADER_HEADER_
/// EOF
