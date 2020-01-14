///
/// @file   texture_loader.hpp
/// @author 板場
///
/// @brief  テクスチャローダー
///
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#include "interface.hpp"
#include "texture.hpp"
BEGIN_EGEG
class ITextureLoader :
    public Interface
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
    virtual bool load( const wchar_t* FilePath, ITexture** ppTexture ) = 0;

protected :
    virtual ~ITextureLoader() override = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
/// EOF
