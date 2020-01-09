///
/// @file   texture_loader.hpp
/// @author 板場
///
/// @brief  テクスチャリソースローダーのインターフェイス
/// 
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#include "interface.hpp"
#include "texture.hpp"
BEGIN_EG_EG
class ITextureLoader :
    public Interface
{
public :
    ///
    /// @brief  テクスチャのロード
    ///
    /// @param[in] FilePath : リソースのファイルパス
    /// @param[out] ppOutTexture : ロードしたテクスチャを受け取るインターフェイス
    ///
    /// @return ロードに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    virtual bool load( const wchar_t* FilePath, ITexture** ppOutTexture ) = 0;

protected :
    ~ITextureLoader() = default;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
///  EOF
