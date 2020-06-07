// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "default_base_scene.hpp"
#include "application_status.hpp"
#include "egeg_math.hpp"
#include "engine.hpp"
#include "table.hpp"
#include "task_order.hpp"
#include "transform2d_component.hpp"
#include "transform3d_component.hpp"


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
    constexpr std::array<float, 4> kClearColor{ 1.0F, 1.0F, 1.0F, 1.0F };
    constexpr D3D11_VIEWPORT kViewport
    {
        0.0F,
        0.0F,
        kWindowWidth<float>,
        kWindowHeight<float>,
        0.0F,
        1.0F
    };
    constexpr D3D11_BUFFER_DESC kCBufferDesc
    {
        sizeof( DirectX::XMFLOAT4X4 ),  // ByteWidth
        D3D11_USAGE_DYNAMIC,            // Usage
        D3D11_BIND_CONSTANT_BUFFER,     // BindFlags
        D3D11_CPU_ACCESS_WRITE,         // CPUAccessFlags
        0,                              // MiscFlags
        0                               // StruxtureByteStride
    };
    constexpr D3D11_TEXTURE2D_DESC kDepthStencilTextureDesc
    {
        kWindowWidth<UINT>,         // Width
        kWindowHeight<UINT>,        // Height
        1,                          // MipLevels
        1,                          // ArraySize
        DXGI_FORMAT_D32_FLOAT,      // Format
        DXGI_SAMPLE_DESC            // SampleDesc
        {
            1,  // Count
            0   // Quiality
        },
        D3D11_USAGE_DEFAULT,        // Usage
        D3D11_BIND_DEPTH_STENCIL,   // BindFlags
        0,                          // CPUAccessFalgs
        0                           // MiscFlags
    };
    constexpr D3D11_DEPTH_STENCIL_VIEW_DESC kDepthStencilDesc
    {
        kDepthStencilTextureDesc.Format,    // Format
        D3D11_DSV_DIMENSION_TEXTURE2D,      // ViewDimension
        0,                                  // Flags
        0                                   // Texture2D.MipSlice
    };
    constexpr D3D11_BLEND_DESC kBlendDesc
    {
        false,  // AlphaToCoverageEnable
        false,  // IndependentBlendEnable
        D3D11_RENDER_TARGET_BLEND_DESC
        {
            true,                           // BlendEnable
            D3D11_BLEND_SRC_ALPHA,          // SrcBlend
            D3D11_BLEND_INV_SRC_ALPHA,      // DestBlend
            D3D11_BLEND_OP_ADD,             // BlendOp
            D3D11_BLEND_ONE,                // SrcBlendAlpha
            D3D11_BLEND_ZERO,               // DestBlendAlpha
            D3D11_BLEND_OP_ADD,             // BlendOpAlpha
            D3D11_COLOR_WRITE_ENABLE_ALL    // RenderTargetWriteMask
        },
        {}, // not use
        {}, // not use
        {}, // not use
        {}, // not use
        {}, // not use
        {}, // not use
        {}, // not use
    };
}


/******************************************************************************

    DefaultBaseScene

******************************************************************************/
 // 初期化
bool DefaultBaseScene::initialize( std::istream& DataStream )
{
    if( !initializeSceneState() ) return false;

    task_.setJob( this, &DefaultBaseScene::render );
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kRenderEnd );

    return true;
}

 
 // 終了
void DefaultBaseScene::finalize()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_ );
}


 // 描画を登録
void DefaultBaseScene::entry( RenderComponent* Component )
{
    models_.push_back( Component );
}


 // 登録を解除
void DefaultBaseScene::exit( RenderComponent* Component )
{
    auto find_itr = ::std::find(models_.begin(), models_.end(), Component);
    if( find_itr != models_.end() )
    {
        models_.erase( find_itr );
    }
}


 // ライト追加
void DefaultBaseScene::addLight( LevelLight* ) {}


 // 描画
void DefaultBaseScene::render( uint64_t )
{
    auto device_context = EasyEngine::getRenderingManager()->getD3DDeviceContext();

    device_context->ClearRenderTargetView( render_target_.Get(), kClearColor.data() );
    device_context->ClearDepthStencilView( depth_stencil_.Get(), D3D11_CLEAR_DEPTH, 1.0F, 0 );

    if( !updateViewMatrix(device_context.Get()) ) return;
    bulidPipeline( device_context.Get() );

    for( const auto& model : models_ )
    {
        if( !model->getState() ) continue;
        if( !updateWorldMatrix(device_context.Get(), model->getOwner()) ) return;

        device_context->IASetIndexBuffer( model->getMesh()->vertices.get<TagVertexIndex>().Get(), DXGI_FORMAT_R32_UINT, 0 );
        
        auto vertices_data = model->getMesh()->vertices.extraction<TagVertexPosition, TagVertexUV, TagVertexNormal>();
        for( const auto& mesh : model->getMesh()->sub_mesh_list )
        {
            mesh.shader->shading( device_context.Get(), vertices_data, mesh.material );
            device_context->DrawIndexed( mesh.num_vertices, mesh.start_index, mesh.base_vertex );
        }
    }
}


 // 描画に関する状態を初期化
 //
 // 失敗して途中で関数を抜けたときに自動で解放されるように
 // 生成したオブジェクトの保持を遅延させている
bool DefaultBaseScene::initializeSceneState()
{
    using namespace Microsoft::WRL;

    auto d3d_device = EasyEngine::getRenderingManager()->getD3DDevice();

    // シェーダー用定数バッファを生成
    ComPtr<ID3D11Buffer> proj{};
    ComPtr<ID3D11Buffer> view{};
    ComPtr<ID3D11Buffer> wrld{};
    Matrix4x4 projection{};
    projection = DirectX::XMMatrixPerspectiveFovLH( kFovAngleY, kAspectRatio, kNearClip, kFarClip );
    projection = DirectX::XMMatrixTranspose( projection );  // シェーダーでは列優先配置なので合わせる
    D3D11_SUBRESOURCE_DATA srd{ &projection, 0U, 0U };
    if( FAILED(d3d_device->CreateBuffer( &kCBufferDesc, &srd,    &proj )) ) return false;
    if( FAILED(d3d_device->CreateBuffer( &kCBufferDesc, nullptr, &view )) ) return false;
    if( FAILED(d3d_device->CreateBuffer( &kCBufferDesc, nullptr, &wrld )) ) return false;

    // 深度バッファを生成
    ComPtr<ID3D11Texture2D> d_tex{};
    ComPtr<ID3D11DepthStencilView> dsv{};
    if( FAILED(d3d_device->CreateTexture2D( &kDepthStencilTextureDesc, nullptr, &d_tex )) ) return false;
    if( FAILED(d3d_device->CreateDepthStencilView(d_tex.Get(), &kDepthStencilDesc, &dsv )) ) return false;

    // ブレンドステートを生成
    ComPtr<ID3D11BlendState> bs{};
    if( FAILED(d3d_device->CreateBlendState( &kBlendDesc, &bs )) ) return false;

    
    cbuffers_.at(kProjection) = proj;
    cbuffers_.at(kView)       = view;
    cbuffers_.at(kWorld)      = wrld;
    render_target_            = EasyEngine::getRenderingManager()->getMainRenderTarget();
    depth_stencil_            = dsv;
    blend_state_              = bs;

    return true;
}


 // パイプラインを構築
 //
 // シェーダーステージ、頂点バッファ等シェーダ―クラスが担うところもあるので、
 // この関数内で全てをセットしていない
void DefaultBaseScene::bulidPipeline( ID3D11DeviceContext* DC )
{
    DC->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    const std::array<ID3D11Buffer*, 3> kCBuffers
    {
        cbuffers_.at(kProjection).Get(), 
        cbuffers_.at(kView).Get(),
        cbuffers_.at(kWorld).Get()
    };
    DC->VSSetConstantBuffers( 0, 3, kCBuffers.data() );
    DC->RSSetViewports( 1, &kViewport );
    DC->RSSetState( nullptr );
    DC->RSSetScissorRects( 0, nullptr );
    ID3D11RenderTargetView* rtv = render_target_.Get();
    DC->OMSetRenderTargets( 1, &rtv, depth_stencil_.Get() );
    const std::array<float, 4> kBlendFactor{ 0.0F, 0.0F, 0.0F, 0.0F };
    DC->OMSetBlendState( blend_state_.Get(), kBlendFactor.data(), 0xFFFFFFFF );
    DC->OMSetDepthStencilState( nullptr, 0 );
}


 // ビュー変換行列を更新
bool DefaultBaseScene::updateViewMatrix( ID3D11DeviceContext* DC ) const
{
    Matrix4x4 view;
    if( camera_ )
        view = DirectX::XMMatrixTranspose( camera_->calcViewMatrix() );
    else
        view = DirectX::XMMatrixIdentity();

    D3D11_MAPPED_SUBRESOURCE mpd{};
    HRESULT hr = DC->Map( cbuffers_.at(kView).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mpd );
    if( FAILED(hr) ) return false;
    memcpy( mpd.pData, &view, sizeof(DirectX::XMFLOAT4X4) );
    DC->Unmap( cbuffers_.at(kView).Get(), 0 );
}


 // ワールド変換行列を更新
bool DefaultBaseScene::updateWorldMatrix( ID3D11DeviceContext* DC, LevelNode* Node ) const
{
    // ワールド変換行列を計算
    // 優先度は 3D->2D の順。座標変換コンポーネントが無ければ単位行列
    auto* transform3d = Node->getComponent<Transform3DComponent>();
    auto* transform2d = Node->getComponent<Transform2DComponent>();
    Matrix4x4 world;
    if( transform3d )
        world = DirectX::XMMatrixTranspose( transform3d->calcGlobalTransformMatrix() );
    else if( transform2d )
        world = DirectX::XMMatrixTranspose( transform2d->calcGlobalTransformMatrix() );
    else
        world = DirectX::XMMatrixIdentity();

    D3D11_MAPPED_SUBRESOURCE mpd{};
    HRESULT hr = DC->Map(cbuffers_.at(kWorld).Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mpd );
    if( FAILED(hr) ) return false;
    memcpy( mpd.pData, &world, sizeof(DirectX::XMFLOAT4X4) );
    DC->Unmap( cbuffers_.at(kWorld).Get(), 0 );
}

END_EGEG
// EOF
