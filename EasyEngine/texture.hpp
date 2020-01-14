///
/// @file   texture.hpp
/// @author 板場
///
/// @brief  テクスチャリソース
///
#ifndef INCLUDED_EGEG_TEXTURE_HEADER_
#define INCLUDED_EGEG_TEXTURE_HEADER_
#include "interface.hpp"
BEGIN_EGEG
class ITexture :
    public Interface
{
protected :
    virtual ~ITexture() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_HEADER_
/// EOF
