// �쐬�� : ��
#include "scene3d.hpp"
#include "rendering3d_component.hpp"

BEGIN_EGEG

// Scene3D �֐���`
/*===========================================================================*/
// ������
bool Scene3D::initialize()
{
    // �萔�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof( DirectX::XMFLOAT4X4 );
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    Microsoft::WRL::ComPtr<ID3D11Device> device;
    immediate_context_->GetDevice( &device );
    
    // �ˉe�ϊ��s��p�萔�o�b�t�@�̍쐬
    DirectX::XMFLOAT4X4 projection;
    DirectX::XMStoreFloat4x4(
        &projection,
        DirectX::XMMatrixPerspectiveFovLH( 30.0F, 1280.0F / 720.0F, 1.0F, 100.0F )
    );
    D3D11_SUBRESOURCE_DATA srd {};
    srd.pSysMem = &projection;
    HRESULT hr = device->CreateBuffer( 
        &desc, &srd, &cbuffers_.at(0) );
    if( FAILED(hr) ) return false;
    ID3D11Buffer* buf = cbuffers_.at( 0 ).Get();
    immediate_context_->VSSetConstantBuffers( 0, 1, &buf );
    
    // �r���[�ϊ��s��p�萔�o�b�t�@�̍쐬
    hr = device->CreateBuffer(
        &desc, nullptr, &cbuffers_.at(1) );
    if( FAILED(hr) ) return false;

    // ���[���h�ϊ��s��p�萔�o�b�t�@�̍쐬
    hr = device->CreateBuffer(
        &desc, nullptr, &cbuffers_.at(2) );
    if( FAILED(hr) ) return false;
    
    return true;
}

// �I������
void Scene3D::finalize()
{

}

// �`��
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
    // �V�[���ŋ��ʂ̐ݒ�
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

    // �r���[�ϊ��s��̐ݒ�
    D3D11_MAPPED_SUBRESOURCE mapped_subresource;
    HRESULT hr = immediate_context_->Map(
        cbuffers_.at(1).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
    if( FAILED(hr) ) return;
    memcpy( mapped_subresource.pData, &camera_->getViewMatrix(), sizeof(DirectX::XMFLOAT4X4) );
    immediate_context_->Unmap( cbuffers_.at(1).Get(), 0 );

    ID3D11Buffer* buf = cbuffers_.at( 1 ).Get();
    immediate_context_->VSSetConstantBuffers( 1, 1, &buf );

    // ���f���̕`��
    for( auto& model : model_list_ )
    {
        Rendering3DComponent* component = model->getComponent<Rendering3DComponent>();
        if( component == nullptr ) continue;

        auto vertex_binder = component->getVertexShader()->getVertexBinder();
        auto vertex = vertex_binder.bind( component->getMesh() );
        if( vertex == false ) continue;

        // ���_���̃Z�b�g
        immediate_context_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        immediate_context_->IASetVertexBuffers( 0, vertex.get().buffers.size(), vertex.get().buffers.data(), vertex.get().strides.data(), vertex.get().offsets.data() );
        immediate_context_->IASetIndexBuffer( component->getMesh()->getIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0 );

        // �V�F�[�_�\�̃Z�b�g
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
        
        // ���[���h�ϊ��s��̐ݒ�
        hr = immediate_context_->Map(
        cbuffers_.at(2).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
        if( FAILED(hr) ) return;
        DirectX::XMFLOAT4X4 world{};
        world._11 = 1.0F; world._14 = model->getPosition().x;
        world._22 = 1.0F; world._24 = model->getPosition().y;
        world._33 = 1.0F; world._33 = model->getPosition().z;
        world._44 = 1.0F;
        memcpy( mapped_subresource.pData, &world, sizeof world );
        immediate_context_->Unmap( cbuffers_.at(2).Get(), 0 );
        ID3D11Buffer* world_buf = cbuffers_.at( 2 ).Get();
        immediate_context_->VSSetConstantBuffers( 2, 1, &world_buf );

        // �`��
        immediate_context_->DrawIndexed(
            component->getMesh()->getNumVertices(),
            0,
            0
        );
    }

    // �`��I��
    model_list_.clear();
}

END_EGEG
// EOF
