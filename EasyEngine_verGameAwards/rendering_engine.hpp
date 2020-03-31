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
#include "detailed_returnvalue.hpp"
BEGIN_EGEG
class ShaderLoader;
class WavefrontOBJLoader;

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

/* 取得関数 */

    ///< 使用しているDirect3Dの機能レベルの取得
    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return feature_level_; }
    ///< 使用しているデバイスの取得
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const noexcept { return device_; }
    ///< デバイスコンテキストの取得
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getImmediateContext() const noexcept { return immediate_context_; }

    ///< シェーダ―ローダーの取得
    ShaderLoader* getShaderLoader() const noexcept { return shader_loader_.get(); }
    ///< モデルローダーの取得
    WavefrontOBJLoader* getModelLoader() const noexcept { return model_loader_.get(); }

/* 生成関数 */

    ///
    /// @brief   バッファオブジェクトの生成 with 初期データ
    /// @details バッファサイズは内部で計算しています。
    ///
    /// @param[in] BufferDesc : 生成するバッファの定義
    /// @param[in] Source     : バッファに格納するデータ
    ///
    /// @return 生成したバッファ
    ///
    template <class DataType>
    DetailedReturnValue<bool> createBuffer( D3D11_BUFFER_DESC* BufferDesc, const std::vector<DataType>& Source, ID3D11Buffer** Output );

private :
    RenderingEngine() = default;

    D3D_FEATURE_LEVEL feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_ = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context_ = nullptr;

    std::unique_ptr<ShaderLoader> shader_loader_;
    std::unique_ptr<WavefrontOBJLoader> model_loader_;
};

// バッファオブジェクトの生成
template <class DataType>
DetailedReturnValue<bool> RenderingEngine::createBuffer( D3D11_BUFFER_DESC* Desc, const std::vector<DataType>& Source, ID3D11Buffer** Output )
{
    using RetTy = DetailedReturnValue<bool>;

    Desc->ByteWidth = sizeof(DataType) * Source.size();
    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem = Source.data();

    HRESULT hr = device_->CreateBuffer(
        Desc, &srd, Output );
    if( FAILED(hr) ) return RetTy( false, "バッファオブジェクトの生成に失敗" );

    return RetTy( true );
}

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
/// EOF
