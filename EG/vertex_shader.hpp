///
/// @file   vertex_shader.hpp
/// @author 板場
///
/// @brief  頂点シェーダインターフェイス
///
#ifndef INCLUDED_EG_EG_VERTEX_SHADER_HEADER_
#define INCLUDED_EG_EG_VERTEX_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EG_EG
class IVertexShader :
    public Interface
{
public :
protected :
    virtual ~IVertexShader() = default;
};
END_EG_EG
#endif /// INCLUDED_EG_EG_VERTEX_SHADER_HEADER_
/// EOF
