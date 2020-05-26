///
/// @file   rendering_manager.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_HEADER_

#include <memory>
#include <wrl.h>
#include <d3d11.h>
#include "non_copyable.hpp"
#include "texture_loader.hpp"
#include "shader_loader.hpp"
#include "wavefrontobj_loader.hpp"

BEGIN_EGEG

///
/// @class RenderingManager
/// @brief 描画マネージャ―
///
class RenderingManager final :
    NonCopyable<RenderingManager>
{
public :
    static std::unique_ptr<RenderingManager> create();
    ~RenderingManager();

    ///
    /// @brief 採用された機能レベルの取得
    ///
    /// @return 採用された機能レベル
    ///
    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return d3d_feature_level_; }

    ///
    /// @brief D3Dデバイスの取得
    ///
    /// @return D3Dデバイス
    ///
    Microsoft::WRL::ComPtr<ID3D11Device> getD3DDevice() const noexcept { return d3d_device_; }

    ///
    /// @brief D3Dデバイスコンテキストの取得
    ///
    /// @return D3Dデバイスコンテキスト
    ///
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getD3DDeviceContext() const noexcept { return d3d_immediate_context_; }

    ///
    /// @brief  テクスチャローダーの取得
    ///
    /// @return テクスチャローダー
    ///
    TextureLoader* getTextureLoader() const noexcept { return texture_loader_.get(); };

    ///
    /// @brief  シェーダーローダーの取得
    ///
    /// @return シェーダーローダー
    ///
    ShaderLoader* getShaderLoader() const noexcept { return shader_loader_.get(); }

    ///
    /// @brief  WavefrontOBJ形式ファイル用ローダーの取得
    ///
    /// @return モデルローダー
    ///
    WavefrontobjLoader* getObjLoader() const noexcept { return obj_loader_.get(); }

private :
    RenderingManager() = default;

    D3D_FEATURE_LEVEL d3d_feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_immediate_context_;
    std::unique_ptr<TextureLoader> texture_loader_;
    std::unique_ptr<ShaderLoader>  shader_loader_;
    std::unique_ptr<WavefrontobjLoader> obj_loader_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
/// EOF
