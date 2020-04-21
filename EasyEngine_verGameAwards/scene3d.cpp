// 作成者 : 板場
#include "scene3d.hpp"
#include "application_status.hpp"
#include "rendering3d.hpp"
#include "transform3d.hpp"

BEGIN_EGEG

// Scene3D 関数定義
/*===========================================================================*/
// 初期化
bool Scene3D::initialize( RenderingManager* Manager )
{
    using namespace DirectX;

    // 定数バッファの作成
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof( XMFLOAT4X4 );
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    
    // 射影変換行列用定数バッファの作成
    XMFLOAT4X4 projection{};
    XMStoreFloat4x4(
        &projection,
        XMMatrixTranspose(
            XMMatrixPerspectiveFovLH( 
                XMConvertToRadians(45.0F), kHorizontalResolution<float> / kVerticalResolution<float>, 0.1F, 100.F 
            )
        )
    );
    D3D11_SUBRESOURCE_DATA srd {};
    srd.pSysMem = &projection;
    HRESULT hr = Manager->getDevice()->CreateBuffer( &desc, &srd, &cbuffers_.at(0) );
    if( FAILED(hr) ) return false;

    // ビュー変換行列用定数バッファの作成
    hr = Manager->getDevice()->CreateBuffer( &desc, nullptr, &cbuffers_.at(1) );
    if( FAILED(hr) ) return false;

    // ワールド変換行列用定数バッファの作成
    hr = Manager->getDevice()->CreateBuffer( &desc, nullptr, &cbuffers_.at(2) );
    if( FAILED(hr) ) return false;
    
    return true;
}

// 終了処理
void Scene3D::finalize()
{

}

// 準備
void Scene3D::prepare()
{
    actor_list_.clear();
}

// 描画
void Scene3D::render(
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
    // シーンの設定
    setSceneState(
        DeviceContext,
        RenderTargetViews,
        Viewports,
        ScissorRects,
        DepthStencilView,
        DepthStencilState,
        StencilRef,
        RasterizerState,
        BlendState,
        BlendFactor,
        BlendMask );

    // 射影変換行列の設定
    ID3D11Buffer* buf[2];
    buf[0] = cbuffers_.at( 0 ).Get();

    // ビュー変換行列の設定
    D3D11_MAPPED_SUBRESOURCE mapped_subresource;
    HRESULT hr = DeviceContext->Map(
        cbuffers_.at(1).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
    if( FAILED(hr) ) return;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4( &view, DirectX::XMMatrixTranspose(camera_->calcViewMatrix()) );
    memcpy( mapped_subresource.pData, &view, sizeof(DirectX::XMFLOAT4X4) );
    DeviceContext->Unmap( cbuffers_.at(1).Get(), 0 );

    buf[1] = cbuffers_.at( 1 ).Get();
    DeviceContext->VSSetConstantBuffers( 0, 2, buf );

    // モデルの描画
    for( auto& actor : actor_list_ )
    {
        auto component = actor->getComponent<component::Rendering3D>();
        if( component == nullptr ) continue;

        auto vertex = component->getVertexShader()->bindVertices(component->getMesh()->vertices);
        if( vertex == false ) continue;

        // 頂点情報のセット
        DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        DeviceContext->IASetVertexBuffers( 0, vertex.get().buffers.size(), vertex.get().buffers.data(), vertex.get().strides.data(), vertex.get().offsets.data() );
        DeviceContext->IASetIndexBuffer( component->getMesh()->vertices.get<Tag_VertexIndex>().Get(), DXGI_FORMAT_R32_UINT, 0 );

        // シェーダ―のセット
        auto setShader = [this, DeviceContext]( Shader* Set )
        {
            Set->setShaderOnPipeline( DeviceContext );
            Set->setConstantBuffersOnPipeline( DeviceContext );
            Set->setSamplersOnPipeline( DeviceContext );
            Set->setShaderResourcesOnPipeline( DeviceContext );
        };
        component->getVertexShader()->setInputLayoutOnPipeline( DeviceContext );
        setShader( component->getVertexShader() );
        if( component->getGeometryShader() ) setShader( component->getGeometryShader() );
        else DeviceContext->GSSetShader( nullptr, nullptr, 0 );
        setShader( component->getPixelShader() );
        
        // ワールド変換行列の設定
        hr = DeviceContext->Map(
        cbuffers_.at(2).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
        if( FAILED(hr) ) return;
        DirectX::XMFLOAT4X4 world;
        if( auto transform = actor->getComponent<component::Transform3D>() )
        { // 座標変換コンポーネントがある場合、変換行列を作成
            Matrix4x4 translation = DirectX::XMMatrixTranslationFromVector( transform->getPosition() );
            Matrix4x4 scaling = DirectX::XMMatrixScalingFromVector( transform->getScale() );
            Vector3D rotation_rad = transform->getRotation();
            rotation_rad.x = DirectX::XMConvertToRadians( rotation_rad.x );
            rotation_rad.y = DirectX::XMConvertToRadians( rotation_rad.y );
            rotation_rad.z = DirectX::XMConvertToRadians( rotation_rad.z );
            Matrix4x4 rotation = DirectX::XMMatrixRotationRollPitchYawFromVector( rotation_rad );
            DirectX::XMMATRIX wor = DirectX::XMMatrixMultiply(scaling, rotation);
            wor = DirectX::XMMatrixMultiply( wor, translation );
            DirectX::XMStoreFloat4x4( &world, DirectX::XMMatrixTranspose(wor) );
        }
        else
        { // 座標変換コンポーネントがない場合、単位行列を変換行列とする。
            DirectX::XMStoreFloat4x4( &world, DirectX::XMMatrixIdentity() );
        }
        memcpy( mapped_subresource.pData, &world, sizeof world );
        DeviceContext->Unmap( cbuffers_.at(2).Get(), 0 );
        ID3D11Buffer* world_buf = cbuffers_.at( 2 ).Get();
        DeviceContext->VSSetConstantBuffers( 2, 1, &world_buf );

        // 描画
        for( auto& submesh : component->getMesh()->submesh_list )
        {
            DeviceContext->DrawIndexed(
                submesh.num_vertices,
                submesh.start_index,
                0
            );
        }
    }
}

END_EGEG
// EOF
