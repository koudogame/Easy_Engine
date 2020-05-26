// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "scene.hpp"
#include <DirectXMath.h>
#include "application_status.hpp"
#include "egeg_math.hpp"
#include "rendering_component.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    enum
    {
        kProjection,
        kView,
        kWorld
    };
    constexpr float kFovAngleY = DirectX::XMConvertToRadians( 45.0F );
    constexpr float kAspectRatio = kWindowWidth<float> / kWindowHeight<float>;
    constexpr float kNearClip = 0.1F;
    constexpr float kFarClip  = 100.0F;
}


/******************************************************************************

	Scene

******************************************************************************/
 // 初期化
bool Scene::initialize( ID3D11Device* Device )
{
    using namespace Microsoft::WRL;
    using namespace DirectX;

    // 定数バッファの作成
    D3D11_BUFFER_DESC buffer_desc{};
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.ByteWidth = sizeof( XMFLOAT4X4 );
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
     // 射影変換行列用
    XMFLOAT4X4 projection{};
    XMStoreFloat4x4(
        &projection,
        XMMatrixTranspose( 
            XMMatrixPerspectiveFovLH( kFovAngleY, kAspectRatio, kNearClip, kFarClip)
        )
    );
    D3D11_SUBRESOURCE_DATA srd{ &projection, 0U, 0U };
    ComPtr<ID3D11Buffer> cbuf_proj{};
    HRESULT hr = Device->CreateBuffer( &buffer_desc, &srd, &cbuf_proj );
    if( FAILED(hr) )    return false;
     // ビュー変換行列用
    ComPtr<ID3D11Buffer> cbuf_view{};
    hr = Device->CreateBuffer( &buffer_desc, nullptr, &cbuf_view );
    if( FAILED(hr) ) return false;
     // ワールド変換行列用
    ComPtr<ID3D11Buffer> cbuf_worl{};
    hr = Device->CreateBuffer( &buffer_desc, nullptr, &cbuf_worl );
    if( FAILED(hr) ) return false;

    cbuffers_.at(kProjection) = std::move( cbuf_proj );
    cbuffers_.at(kView)       = std::move( cbuf_view );
    cbuffers_.at(kWorld)      = std::move( cbuf_worl );

	return true;
}


 // 終了
void Scene::finalize()
{
    cbuffers_.at(kProjection) = nullptr;
    cbuffers_.at(kView) = nullptr;
    cbuffers_.at(kWorld) = nullptr;
}


 // ステート設定
void Scene::setState(
        std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> RenderTargetViews,
        std::vector<D3D11_VIEWPORT> Viewports,
        std::vector<D3D11_RECT> ScissorRects,
        const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& DepthStencilView,
        const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& DepthStencilState,
        UINT StencilReference,
        const Microsoft::WRL::ComPtr<ID3D11RasterizerState>& RasterizerState,
        const Microsoft::WRL::ComPtr<ID3D11BlendState>& BlendState,
        const std::array<float, 4U>& BlendFactor,
        UINT BlendMask ) noexcept
{
    render_target_views_ = std::move(RenderTargetViews);
    viewports_ = std::move(Viewports);
    scissor_rects_ = std::move(ScissorRects);
    depth_stencil_view_ = DepthStencilView;
    depth_stencil_state_ = DepthStencilState;
    stencil_reference_ = StencilReference;
    rasterizer_state_ = RasterizerState;
    blend_state_ = BlendState;
    blend_factor_ = BlendFactor;
    blend_mask_ = BlendMask;
}


 // クリア
void Scene::clear( ID3D11DeviceContext* DC, const std::array<float, 4U>& Color )
{
    for( auto& rtv : render_target_views_ )
        DC->ClearRenderTargetView( rtv.Get(), Color.data() );
}

 // 描画
void Scene::render( ID3D11DeviceContext* DC )
{
    using namespace DirectX;

    DC->ClearDepthStencilView( depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH, 1.0F, 0 );
 
    std::vector<ID3D11RenderTargetView*> render_target_views;
    render_target_views.reserve( render_target_views_.size() );
    for( auto& rtv : render_target_views_ )
        render_target_views.push_back( rtv.Get() );
    DC->OMSetRenderTargets( render_target_views.size(), render_target_views.data(), depth_stencil_view_.Get() );
    DC->OMSetDepthStencilState( depth_stencil_state_.Get(), stencil_reference_ );
    DC->OMSetBlendState( blend_state_.Get(), blend_factor_.data(), blend_mask_ );
    DC->RSSetState( rasterizer_state_.Get() );
    DC->RSSetViewports( viewports_.size(), viewports_.data() );
    DC->RSSetScissorRects( scissor_rects_.size(), scissor_rects_.data() );
    
    ID3D11Buffer* cbuffers[3];
    for( int i = 0; i < 3; ++i )
        cbuffers[i] = cbuffers_.at(i).Get();

    // 定数バッファのビュー変換行列を更新
    XMFLOAT4X4 view{};
    if( !camera_ )
        XMStoreFloat4x4( &view, XMMatrixIdentity() );
    else
        XMStoreFloat4x4( &view, XMMatrixTranspose(camera_->calcViewMatrix()) );
    D3D11_MAPPED_SUBRESOURCE mpd{};
    HRESULT hr = DC->Map( cbuffers[kView], 0, D3D11_MAP_WRITE_DISCARD, 0, &mpd );
    if( FAILED(hr) ) return;
    memcpy( mpd.pData, &view, sizeof(XMFLOAT4X4) );
    DC->Unmap( cbuffers[kView], 0 );

    for( const auto& model : models_ )
    {
        if( !model->getState() ) continue;

        // 定数バッファのワールド変換行列を更新
        XMFLOAT4X4 world{};
        XMStoreFloat4x4( 
            &world, 
            XMMatrixTranspose(model->getOwner()->calcWorldMatrix())
        );
        hr = DC->Map( cbuffers[kWorld], 0, D3D11_MAP_WRITE_DISCARD, 0, &mpd );
        if( FAILED(hr) ) return;
        memcpy( mpd.pData, &world, sizeof(XMFLOAT4X4) );
        DC->Unmap( cbuffers[kWorld], 0 );
        DC->VSSetConstantBuffers( 0, 3, cbuffers );

        // モデルの描画
        DC->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        DC->IASetIndexBuffer( model->getMesh().vertices.get<TagVertexIndex>().Get(), DXGI_FORMAT_R32_UINT, 0 );
        IShader::VertexData vertices = model->getMesh().vertices.extraction<
            TagVertexPosition,
            TagVertexUV,
            TagVertexNormal>();
        for( const auto& kMesh : model->getMesh().sub_mesh_list )
        {
            kMesh.shader->shading( DC, vertices, kMesh.material );
            DC->DrawIndexed( kMesh.num_vertices, kMesh.start_index, kMesh.base_vertex );
        }
    }
}

END_EGEG
// EOF
