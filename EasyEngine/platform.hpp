///
/// @file   platform.hpp
/// @author 板場
///
/// @brief  プラットフォーム
///
#ifndef INCLUDED_EGEG_PLATFORM_HEADER_
#define INCLUDED_EGEG_PLATFORM_HEADER_
#include "interface.hpp"
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class IPlatform :
    public Interface
{
public :
    ///
    /// @brief  レンダラーの生成
    ///
    /// @return 生成したレンダラー
    ///
    virtual IRenderer* createRenderer() const = 0;

    ///
    /// @brief  シェーダーローダーの生成
    ///
    /// @return 生成したシェーダーローダー
    ///
    virtual IShaderLoader* createShaderLoader() const = 0;

    ///
    /// @brief  テクスチャローダーの生成
    ///
    /// @return 生成したテクスチャローダー
    ///
    virtual ITextureLoader* createTextureLoader() const = 0;

protected :
    virtual ~IPlatform() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_HEADER_
/// EOF
