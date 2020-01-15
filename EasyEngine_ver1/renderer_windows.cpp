// 作成者 : 板場
#include "renderer_windows.hpp"

BEGIN_EGEG
// RendererWindows : 関数の実装
/*===========================================================================*/
// コンストラクタ
RendererWindows::RendererWindows( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain ) :
    p_device_( pDevice ),
    p_immediate_context_( pImmediateContext ),
    p_swap_chain_( pSwapChain )
{
    p_device_->AddRef();
    p_immediate_context_->AddRef();
    p_swap_chain_->AddRef();
}

// デストラクタ
RendererWindows::~RendererWindows()
{
    p_render_target_view_->Release();
    p_swap_chain_->Release();
    p_immediate_context_->Release();
    p_device_->Release();
}

// 初期化
bool RendererWindows::initialize()
{
    // パイプラインにレンダーターゲットビューを設定
    ID3D11Texture2D* backbuffer;
    if (FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer)))
    {
        return false;
    }
    if (FAILED(p_device_->CreateRenderTargetView(backbuffer, nullptr, &p_render_target_view_)))
    {
        backbuffer->Release();
        return false;
    }
    p_immediate_context_->OMSetRenderTargets(1U, &p_render_target_view_, nullptr);

    // パイプラインにビューポートを設定
    D3D11_TEXTURE2D_DESC desc;
    backbuffer->GetDesc(&desc);
    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<float>(desc.Width);
    vp.Height = static_cast<float>(desc.Height);
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    p_immediate_context_->RSSetViewports(1U, &vp);

    // 不要になったバッファを開放
    backbuffer->Release();

    return true;
}

// 描画開始
void RendererWindows::beginRender( const Vector4D& Color )
{

}

// 描画エントリー
void RendererWindows::entryRender( const Model& Model )
{
}

// 描画終了
void RendererWindows::endRender()
{

}
END_EGEG
// EOF
