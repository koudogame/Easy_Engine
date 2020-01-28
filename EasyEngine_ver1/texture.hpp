///
/// @file   texture.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TEXTURE_HEADER_
#define INCLUDED_EGEG_TEXTURE_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
///
/// @class ITexture
///
/// @brief  テクスチャデータ
///
class ITexture :
    public SharedObject
{
public :
    ///
    /// @brief  テクスチャの横幅を取得
    ///
    /// @return テクスチャの横幅
    ///
    virtual long getWidth() const = 0;
    ///
    /// @brief  テクスチャの縦幅を取得
    ///
    /// @return テクスチャの縦幅
    ///
    virtual long getHeight() const = 0;

protected :
    virtual ~ITexture() = 0 {}

};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_HEADER_
/// EOF
