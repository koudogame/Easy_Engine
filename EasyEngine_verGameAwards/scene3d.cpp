// 作成者 : 板場
#include "scene3d.hpp"
#include "rendering3d_component.hpp"

BEGIN_EGEG

// Scene3D 関数定義
/*===========================================================================*/
// 描画
void Scene3D::render( 
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
    // シーンで共通の設定
    immediate_context_->OMSetRenderTargets(
        RenderTargetViews.size(),
        RenderTargetViews.data(),
        DepthStencilView );
    immediate_context_->OMSetDepthStencilState( DepthStencilState, StencilRef );
    if( BlendFactor ) 
    {
        immediate_context_->OMSetBlendState( BlendState, BlendFactor, BlendMask );
    }
    else             
    {
        float blend_factor[4] = { 0.0F, 0.0F, 0.0F, 0.0F };
        immediate_context_->OMSetBlendState( BlendState, blend_factor , BlendMask );
    }
    immediate_context_->RSSetState( RasterizerState );
    immediate_context_->RSSetViewports( Viewports.size(), Viewports.data() );
    immediate_context_->RSSetScissorRects( ScissorRects.size(), ScissorRects.data() );

    // モデルの描画
    for( auto& model : model_list_ )
    {
        Rendering3DComponent* component = model->getComponent<Rendering3DComponent>();
        if( component == nullptr ) continue;

        auto vertex_binder = component->getVertexShader()->getVertexBinder();
        auto vertex = vertex_binder.bind( component->getVertexData() );
        if( vertex == false ) continue;

        // 頂点情報のセット
        immediate_context_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
        immediate_context_->IASetVertexBuffers( 0, vertex.get().buffers.size(), vertex.get().buffers.data(), vertex.get().strides.data(), vertex.get().offsets.data() );
        immediate_context_->IASetIndexBuffer( component->getVertexData()->getIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0 );

        // シェーダ―のセット
        auto setShader = [this]( Shader* Set )
        {
            Set->setShaderOnPipeline( immediate_context_.Get() );
            Set->setConstantBuffersOnPipeline( immediate_context_.Get() );
            Set->setSamplersOnPipeline( immediate_context_.Get() );
            Set->setShaderResourcesOnPipeline( immediate_context_.Get() );
        };
        component->getVertexShader()->setInputLayoutOnPipeline( immediate_context_.Get() );
        setShader( component->getVertexShader() );
        if( component->getGeometryShader() ) setShader( component->getGeometryShader() );
        else immediate_context_->GSSetShader( nullptr, nullptr, 0 );
        setShader( component->getPixelShader() );


        // 描画
        immediate_context_->DrawIndexed(
            component->getVertexData()->getNumVertices(),
            0,
            0
        );
    }

    // 描画終了
    model_list_.clear();
}

END_EGEG
// EOF
