///
/// @file   rendering_engine.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#define INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#include <memory>
#include <unordered_map>
#include <wrl.h>
#include <d3d11.h>
#include "noncopyable.hpp"
BEGIN_EGEG
class ShaderLoader;

///
/// @class   RenderingEngine
/// @brief   描画エンジン
/// @details シングルトンクラスです。
///
class RenderingEngine final :
    public std::enable_shared_from_this<RenderingEngine>,
    NonCopyable<RenderingEngine>
{
public :
    ~RenderingEngine();

    static std::shared_ptr<RenderingEngine> create();

    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return feature_level_; }
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const noexcept { return device_; }
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getImmediateContext() const noexcept { return immediate_context_; }

    ///< シェーダ―ローダーの取得
    std::shared_ptr<ShaderLoader> getShaderLoader() const noexcept { return shader_loader_; }

private :
    RenderingEngine() = default;

    D3D_FEATURE_LEVEL    feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_ = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context_ = nullptr;

    std::shared_ptr<ShaderLoader> shader_loader_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
/// EOF
