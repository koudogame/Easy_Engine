// 作成者 : 板場
#include "scene3d.hpp"
#include "rendering3d.hpp"
#include "transform3d.hpp"

BEGIN_EGEG

// Scene3D 関数定義
/*===========================================================================*/
// 初期化
bool Scene3D::initialize( ID3D11Device* Device )
{
    // 定数バッファの作成
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof( DirectX::XMFLOAT4X4 );
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    
    // 射影変換行列用定数バッファの作成
    DirectX::XMFLOAT4X4 projection{};
    DirectX::XMStoreFloat4x4(
        &projection,
        DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH( DirectX::XMConvertToRadians(45.0F), 1280.0F / 720.0F, 0.1F, 10.F ))
    );
    D3D11_SUBRESOURCE_DATA srd {};
    srd.pSysMem = &projection;
    HRESULT hr = Device->CreateBuffer( 
        &desc, &srd, &cbuffers_.at(0) );
    if( FAILED(hr) ) return false;

    // ビュー変換行列用定数バッファの作成
    hr = Device->CreateBuffer(
        &desc, nullptr, &cbuffers_.at(1) );
    if( FAILED(hr) ) return false;

    // ワールド変換行列用定数バッファの作成
    hr = Device->CreateBuffer(
        &desc, nullptr, &cbuffers_.at(2) );
    if( FAILED(hr) ) return false;
    
    return true;
}

// 終了処理
void Scene3D::finalize()
{

}

// 描画
void Scene3D::render(
        ID3D11DeviceContext* ImmediateContext,
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
    ImmediateContext->OMSetRenderTargets(
        RenderTargetViews.size(),
        RenderTargetViews.data(),
        DepthStencilView );
    ImmediateContext->OMSetDepthStencilState( DepthStencilState, StencilRef );
    if( BlendFactor ) 
    {
        ImmediateContext->OMSetBlendState( BlendState, BlendFactor, BlendMask );
    }
    else             
    {
        float blend_factor[4] = { 0.0F, 0.0F, 0.0F, 0.0F };
        ImmediateContext->OMSetBlendState( BlendState, blend_factor , BlendMask );
    }
    ImmediateContext->RSSetState( RasterizerState );
    ImmediateContext->RSSetViewports( Viewports.size(), Viewports.data() );
    ImmediateContext->RSSetScissorRects( ScissorRects.size(), ScissorRects.data() );
    

    // 射影変換行列の設定
    ID3D11Buffer* buf = cbuffers_.at( 0 ).Get();
    ImmediateContext->VSSetConstantBuffers( 0, 1, &buf );

    // ビュー変換行列の設定
    D3D11_MAPPED_SUBRESOURCE mapped_subresource;
    HRESULT hr = ImmediateContext->Map(
        cbuffers_.at(1).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
    if( FAILED(hr) ) return;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4( &view, DirectX::XMMatrixTranspose(camera_->getViewMatrix()) );
    memcpy( mapped_subresource.pData, &view, sizeof(DirectX::XMFLOAT4X4) );
    ImmediateContext->Unmap( cbuffers_.at(1).Get(), 0 );

    buf = cbuffers_.at( 1 ).Get();
    ImmediateContext->VSSetConstantBuffers( 1, 1, &buf );

    // モデルの描画
    for( auto& model : model_list_ )
    {
        auto component = model->getComponent<component::Rendering3D>();
        if( component == nullptr ) continue;

        auto vertex = component->getVertexShader()->bindVertices(model->getComponent<component::Rendering3D>()->getMesh()->vertices);
        if( vertex == false ) continue;

        // 頂点情報のセット
        ImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        ImmediateContext->IASetVertexBuffers( 0, vertex.get().buffers.size(), vertex.get().buffers.data(), vertex.get().strides.data(), vertex.get().offsets.data() );
        ImmediateContext->IASetIndexBuffer( component->getMesh()->vertices.get<Tag_VertexIndex>().Get(), DXGI_FORMAT_R32_UINT, 0 );

        // シェーダ―のセット
        auto setShader = [this, ImmediateContext]( Shader* Set )
        {
            Set->setShaderOnPipeline( ImmediateContext );
            Set->setConstantBuffersOnPipeline( ImmediateContext );
            Set->setSamplersOnPipeline( ImmediateContext );
            Set->setShaderResourcesOnPipeline( ImmediateContext );
        };
        component->getVertexShader()->setInputLayoutOnPipeline( ImmediateContext );
        setShader( component->getVertexShader() );
        if( component->getGeometryShader() ) setShader( component->getGeometryShader() );
        else ImmediateContext->GSSetShader( nullptr, nullptr, 0 );
        setShader( component->getPixelShader() );
        
        // ワールド変換行列の設定
        hr = ImmediateContext->Map(
        cbuffers_.at(2).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
        if( FAILED(hr) ) return;
            DirectX::XMFLOAT4X4 world;
        auto transform = model->getComponent<component::Transform3D>();
        if( transform )
        {
            Matrix4x4 translation = DirectX::XMMatrixTranslationFromVector( transform->getPosition() );
            Matrix4x4 scaling = DirectX::XMMatrixScalingFromVector( transform->getPosition() );
            DirectX::XMMATRIX wor = DirectX::XMMatrixMultiply(translation, scaling);
            DirectX::XMStoreFloat4x4( &world, DirectX::XMMatrixTranspose(translation) );
        }
        else
            DirectX::XMStoreFloat4x4( &world, DirectX::XMMatrixIdentity() );

        memcpy( mapped_subresource.pData, &world, sizeof world );
        ImmediateContext->Unmap( cbuffers_.at(2).Get(), 0 );
        ID3D11Buffer* world_buf = cbuffers_.at( 2 ).Get();
        ImmediateContext->VSSetConstantBuffers( 2, 1, &world_buf );

        // 描画
        for( auto& submesh : model->getComponent<component::Rendering3D>()->getMesh()->submesh_list )
        {
            ImmediateContext->DrawIndexed(
                submesh.num_vertices,
                submesh.start_index,
                0
            );
        }
        
    }

    // 描画終了
    model_list_.clear();
}

END_EGEG
// EOF
