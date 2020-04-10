// �쐬�� : ��
#include "scene2d.hpp"
#include "rendering2d.hpp"
#include "transform2d.hpp"


namespace
{
    enum CBufferIndex : uint32_t
    {
        kView,
        kWorld
    };

    // ���_���W
    const std::vector<EGEG VertexPositionType> kVerticesPosition
    {
        EGEG VertexPositionType{ -1.0F, 1.0F, 0.0F },
        EGEG VertexPositionType{ 1.0F, 1.0F, 0.0F }, 
        EGEG VertexPositionType{ -1.0F, -1.0F, 0.0F },
        EGEG VertexPositionType{ 1.0F, -1.0F, 0.0F }
    };
} // namespace

BEGIN_EGEG

// Scene2D �֐���`
/*===========================================================================*/
// ������
bool Scene2D::initialize( RenderingManager* Engine )
{
    using namespace Microsoft::WRL;

    // �萔�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC cb_desc{};
    cb_desc.Usage = D3D11_USAGE_DYNAMIC;
    cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb_desc.ByteWidth = sizeof( DirectX::XMFLOAT4X4 );
    cb_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // �萔�o�b�t�@�̍쐬
    HRESULT hr;
    for( auto& cbuffer : cbuffer_list_ )
    {
        hr = Engine->getDevice()->CreateBuffer(&cb_desc, nullptr, &cbuffer);
        if( FAILED(hr) ) return false;
    }

    // ���_�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC desc {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    // ���W
    ComPtr<ID3D11Buffer> buffer;
    if( !Engine->createBuffer(&desc, kVerticesPosition, &buffer) ) return false;
    vertices_.set<Tag_VertexPosition>( buffer );
    // UV���W
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = sizeof( VertexUVType ) * 4;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    hr = Engine->getDevice()->CreateBuffer(&desc, nullptr, &buffer);
    if( FAILED(hr) ) return false;
    vertices_.set<Tag_VertexUV>( buffer );

    return true;
}

// �I��
void Scene2D::finalize()
{
    for( auto& cbuffer : cbuffer_list_ )
        cbuffer->Release();
}

// �`�揀��
void Scene2D::prepare()
{
    actor_list_.clear();
}

// �V�[���`��
void Scene2D::render(
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
    UINT BlendMask)
{
    using namespace DirectX;

    // �V�[���̐ݒ�
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

    auto setShader = [this, DeviceContext]( Shader* Set )
    {
        Set->setShaderOnPipeline( DeviceContext );
        Set->setConstantBuffersOnPipeline( DeviceContext );
        Set->setSamplersOnPipeline( DeviceContext );
        Set->setShaderResourcesOnPipeline( DeviceContext );
    };

    ID3D11Texture2D* render_texture;
    RenderTargetViews.at(0)->GetResource( reinterpret_cast<ID3D11Resource**>(&render_texture) );
    D3D11_TEXTURE2D_DESC render_target_texture_desc;
    render_texture->GetDesc( &render_target_texture_desc );
    render_texture->Release();

    float r_screen_width = 1.0F / static_cast<float>(render_target_texture_desc.Width);
    float r_screen_height = 1.0F / static_cast<float>(render_target_texture_desc.Height);
    for( auto& actor : actor_list_ )
    {
        // �`��R���|�[�l���g�擾
        auto component = actor->getComponent<component::Rendering2D>();
        if( component == nullptr ) continue;

        // �V�F�[�_�[�ŗ��p���钸�_�f�[�^���擾
        auto vertex = component->getVertexShader()->bindVertices(vertices_);
        if( !vertex ) continue;

        // �V�F�[�_�[�̃Z�b�g
        component->getVertexShader()->setInputLayoutOnPipeline( DeviceContext );
        setShader( component->getVertexShader() );
        if( auto gs = component->getGeometryShader() )
            setShader( component->getGeometryShader() );
        else
            DeviceContext->GSSetShader( nullptr, nullptr, 0 );
        setShader( component->getPixelShader() );

        // ���[���h�ϊ��s��̌v�Z
        Matrix4x4 world {};
        // �傫���𒲐�
        float width = static_cast<float>( component->getTrimmingRange().right - component->getTrimmingRange().left );
        float height = static_cast<float>( component->getTrimmingRange().bottom - component->getTrimmingRange().top );
        world._11 = width * r_screen_width;
         world._22 = height * r_screen_height;
          world._33 = 1.0F;
           world._44 = 1.0F;
        if( auto transform = actor->getComponent<component::Transform2D>() )
        { // ���W�ϊ��R���|�[�l���g������ꍇ�A����Ɋ�Â��ĕϊ��s����쐬
            Vector2D pivot = transform->getPivot();
            float rotation = XMConvertToRadians(transform->getRotation());
            Vector2D translation = transform->getPosition();
            
            // �������_�ɂȂ�܂ňړ�
            pivot.x = -((pivot.x * 2.0F - 1.0F) * (world._11));
            pivot.y = ((pivot.y * 2.0F - 1.0F) * (world._22));
            world = static_cast<XMMATRIX>(world) * XMMatrixTranslationFromVector(pivot);
            // �g�k
            world = static_cast<XMMATRIX>(world) * XMMatrixScalingFromVector( transform->getScale() );
            // ��]
            world = static_cast<XMMATRIX>(world) * XMMatrixRotationZ( rotation );
            // ���s�ړ�
            translation.x *= r_screen_width * 2.0F;
            translation.x -= 1.0F;
            translation.y *= -r_screen_height * 2.0F;
            translation.y += 1.0F;
            world = static_cast<XMMATRIX>(world) * XMMatrixTranslationFromVector( translation );
        }
        XMStoreFloat4x4( &world, XMMatrixTranspose(world) );
        
        D3D11_MAPPED_SUBRESOURCE mapped_subresource;
        HRESULT hr = DeviceContext->Map(
            cbuffer_list_.at(kWorld), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
        if( FAILED(hr) ) return;
        memcpy( mapped_subresource.pData, &world, sizeof(world) );
        DeviceContext->Unmap( cbuffer_list_.at(kWorld), 0 );
        ID3D11Buffer* wor_buf = cbuffer_list_.at(kWorld);
        DeviceContext->VSSetConstantBuffers( 0, 1, &wor_buf );

        
        ID3D11ShaderResourceView* texture = component->getTexture().Get();
        ID3D11Texture2D* resource;
        texture->GetResource( reinterpret_cast<ID3D11Resource**>(&resource) );
        D3D11_TEXTURE2D_DESC texture_desc;
        resource->GetDesc( &texture_desc );
        resource->Release();

        float left = static_cast<float>(component->getTrimmingRange().left) / texture_desc.Width;
        float top  = static_cast<float>(component->getTrimmingRange().top ) / texture_desc.Height;
        float right = static_cast<float>(component->getTrimmingRange().right) / texture_desc.Width;
        float bottom = static_cast<float>(component->getTrimmingRange().bottom) / texture_desc.Height;
        VertexUVType texcoord[4] =
        {
            {left, top },
            {right, top},
            {left, bottom},
            {right, bottom}
        };
        hr = DeviceContext->Map(
            vertices_.get<Tag_VertexUV>().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource );
        if( FAILED(hr) ) return;
        memcpy( mapped_subresource.pData, texcoord, sizeof(VertexUVType) * 4 );
        DeviceContext->Unmap( vertices_.get<Tag_VertexUV>().Get(), 0 );

        // �e�N�X�`���̃Z�b�g
        DeviceContext->PSSetShaderResources( 0, 1, &texture );
        
        // ���_���̃Z�b�g
        DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
        DeviceContext->IASetVertexBuffers( 0, vertex.get().buffers.size(), vertex.get().buffers.data(), vertex.get().strides.data(), vertex.get().offsets.data() );

        // �`��
        DeviceContext->Draw( 4, 0 );
    }
}

END_EGEG
// EOF
