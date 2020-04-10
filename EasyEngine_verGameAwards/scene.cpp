// 作成者 : 板場
#include "scene.hpp"

BEGIN_EGEG

// Scene 関数定義
/*===========================================================================*/
// シーン設定
void Scene::setSceneState(
    ID3D11DeviceContext* DeviceContext,
        const std::vector<ID3D11RenderTargetView*>& RenderTargetViews,
        const std::vector<D3D11_VIEWPORT>& Viewports,
        const std::vector<D3D11_RECT>& ScissorRects,
        ID3D11DepthStencilView* DepthStencilView,
        ID3D11DepthStencilState* DepthStencilState,
        UINT StencilRef,
        ID3D11RasterizerState* RasterizerState,
        ID3D11BlendState* BlendState,
        float* BlendFactor,
        UINT BlendMask )
{
    DeviceContext->OMSetRenderTargets( RenderTargetViews.size(), RenderTargetViews.data(), DepthStencilView );
    DeviceContext->OMSetDepthStencilState( DepthStencilState, StencilRef );
    if( BlendFactor )
    { // ブレンドファクタに指定がある
        DeviceContext->OMSetBlendState( BlendState, BlendFactor, BlendMask );
    }
    else
    { // ブレンドファクタに指定がない
        float blennd_factor[4] = { 0.0F, 0.0F, 0.0F, 0.0F };
        DeviceContext->OMSetBlendState( BlendState, BlendFactor, BlendMask );
    }
    DeviceContext->RSSetState( RasterizerState );
    DeviceContext->RSSetViewports( Viewports.size(), Viewports.data() );
    DeviceContext->RSSetScissorRects( ScissorRects.size(), ScissorRects.data() );
}

END_EGEG
// EOF
