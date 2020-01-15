///
/// @file   shader.hpp
/// @author 板場
///
/// @brief  シェーダーのインターフェイス
///
#ifndef INCLUDED_EG_EG_SHADER_HEADER_
#define INCLUDED_EG_EG_SHADER_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class IShader :
    public SharedObject
{
protected :
    virtual ~IShader() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_HEADER_
/// EOF
