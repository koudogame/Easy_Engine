///
/// @file   renderer_d3d11.hpp
/// @author 板場
///
/// @brief  Direct3D11を使用したレンダラーです。<br>
///         RendererFactoryにより生成されます。
///
///
#ifndef INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#define INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#include <unordered_map>
#include <Windows.h>
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EG_EG
class RendererD3D11 :
    public IRenderer
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pDevice : D3Dデバイス
    /// @param[in] pImmediateContext : D3Dデバイスコンテキスト
    /// @param[in] pSwapChain : DXGXスワップチェイン
    ///
    RendererD3D11( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain ) :
        p_device_( pDevice ),
        p_immediate_context_( pImmediateContext ),
        p_swap_chain_( pSwapChain )
    {
        p_device_->AddRef();
        p_immediate_context_->AddRef();
        p_swap_chain_->AddRef();
    }
    ///
    /// @brief  初期化処理
    ///
    /// @return 初期化に成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool initialize();

// IRenderer
/*-----------------------------------------------------------------*/
    void beginRender( float* ) override;
    void setVertexShader( IVertexShader* ) override;
    void setPixelShader( IPixelShader* ) override;
    void setTexture( ITexture* ) override;
    void render( const Mesh& ) override;
    void endRender() override;

private :
    ~RendererD3D11();

    ID3D11Device*           p_device_ = nullptr;                /// D3Dデバイスインターフェイス
    ID3D11DeviceContext*    p_immediate_context_ = nullptr;     /// D3Dデバイスコンテキストインターフェイス
    IDXGISwapChain*         p_swap_chain_ = nullptr;            /// DXGIスワップチェインインターフェス
    ID3D11RenderTargetView* p_render_target_view_ = nullptr;    /// D3D描画ターゲットビューインターフェイス
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
/// EOF
