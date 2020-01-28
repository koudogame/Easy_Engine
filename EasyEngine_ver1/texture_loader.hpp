///
/// @file   texture_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#include <string>
#include "texture.hpp"
BEGIN_EGEG
///
/// @class ITextureLoader
///
/// @brief  テクスチャローダー
///
class ITextureLoader
{
public :
    ///
    /// @brief  テクスチャリソースの読み込み
    ///
    /// @param[in] FilePath : 読み込むテクスチャのファイルパス
    /// @param[out] ppTexture : 読み込んだテクスチャを保持するインターフェイス
    ///
    /// @return 読み込み成功[ true ] 読み込み失敗[ false ]
    ///
    virtual bool load( const std::wstring& FilePath, ITexture** ppTexture ) = 0;

    virtual ~ITextureLoader() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
/// EOF
