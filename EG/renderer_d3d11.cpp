// 作成者 : 板場
#include "renderer_d3d11.hpp"
#include <fstream>
#include "DirectXTex/DirectXTex.h"
#include "vertex_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"
#include "texture_d3d11.hpp"

#pragma comment( lib, "d3d11.lib" )

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif

BEGIN_EGEG
// 関数の実装
/*===========================================================================*/
// 描画開始
void RendererD3D11::beginRender(float* Color )
{
    p_immediate_context_->ClearRenderTargetView( p_render_target_view_, Color );
}
// 頂点シェーダ―のセット
void RendererD3D11::setVertexShader( IVertexShader* pVertexShader )
{
    ID3D11VertexShader* p_d3d11_vs = 
        static_cast<VertexShaderD3D11*>(pVertexShader)->get();

    p_immediate_context_->VSSetShader( p_d3d11_vs, nullptr, 0 ); 
}
// ピクセルシェーダのセット
void RendererD3D11::setPixelShader( IPixelShader* pPixelShader )
{
    ID3D11PixelShader* p_d3d11_ps =
        static_cast<PixelShaderD3D11*>(pPixelShader)->get();

    p_immediate_context_->PSSetShader( p_d3d11_ps, nullptr, 0 );
}
// テクスチャのセット
void RendererD3D11::setTexture( ITexture* pTexture )
{
    ID3D11ShaderResourceView* p_d3d11_srv =
        static_cast<TextureD3D11*>(pTexture)->get();

    p_immediate_context_->PSSetShaderResources( 0, 0, &p_d3d11_srv );
}
// モデルの描画
void RendererD3D11::render(const Mesh& Object)
{

}
// 描画終了
void RendererD3D11::endRender()
{
    if( p_swap_chain_->Present(0, DXGI_PRESENT_TEST) == S_OK )
        p_swap_chain_->Present( 0, 0 );
}

// 初期化処理
bool RendererD3D11::initialize()
{
    // 描画ターゲットをパイプラインに設定
    ID3D11Texture2D* buffer;
    if( FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer)) )
        return false;
    if( FAILED(p_device_->CreateRenderTargetView(buffer, nullptr, &p_render_target_view_)) )
    {
        buffer->Release();
        return false;
    }
    p_immediate_context_->OMSetRenderTargets( 1, &p_render_target_view_, nullptr );

    // ビューポートをパイプラインに設定
    D3D11_TEXTURE2D_DESC desc;
    buffer->GetDesc( &desc );
    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<float>(desc.Width);
    vp.Height = static_cast<float>(desc.Height);
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    p_immediate_context_->RSSetViewports( 1, &vp );

    buffer->Release();

    return true;
}

// デストラクタ
RendererD3D11::~RendererD3D11()
{
    // フルスクリーンモードを解除
    p_swap_chain_->SetFullscreenState(false, nullptr);

    // パイプラインのステート設定をクリア
    p_immediate_context_->ClearState();

    // 各種インターフェイスを解放
    p_render_target_view_->Release();
    p_swap_chain_->Release();
    p_immediate_context_->Release();
    p_device_->Release();
}
END_EGEG
// EOF
