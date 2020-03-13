///
/// @file   rendering_engine.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#define INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#include <memory>
#include <unordered_map>
#include <d3d11.h>
#include "egeg_utility.hpp"
BEGIN_EGEG
class VertexShader;
class GeometryShader;
class PixelShader;

///
/// @class   RenderingEngine
/// @brief   描画エンジン
/// @details シングルトンクラスです。2回以上create関数は呼び出さないでください。
///
class RenderingEngine final :
    public std::enable_shared_from_this<RenderingEngine>,
    NonCopyable<RenderingEngine>
{
public :
    ~RenderingEngine();

    static std::shared_ptr<RenderingEngine> create();

    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return feature_level_; }
    ID3D11Device* getDevice() const noexcept { device_->AddRef(); return device_; }
    ID3D11DeviceContext* getDeviceContext() const noexcept { device_context_->AddRef(); return device_context_; }

    ///
    /// @brief   シェーダ―の生成
    ///
    /// @tparam ShaderType : 生成するシェーダー型
    ///
    /// @return 生成したシェーダー
    ///
    template <class ShaderType>
    std::unique_ptr<ShaderType> createShader() const;

    ///
    /// @brief  シーンの生成
    ///
    /// @tparam SceneType : 生成するシーン型
    ///
    /// @return 生成したシーン
    ///
    template <class SceneType>
    std::unique_ptr<SceneType> createScene() const;

private :
    RenderingEngine() = default;

    D3D_FEATURE_LEVEL    feature_level_;
    ID3D11Device*        device_ = nullptr;
    ID3D11DeviceContext* device_context_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
/// EOF
