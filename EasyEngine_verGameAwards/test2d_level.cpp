#include "test2d_level.hpp"
#include "application_status.hpp"
#include "easy_engine.hpp"
#include "rendering_manager.hpp"

USING_NS_EGEG;

bool Test2DLevel::initialize()
{
    using namespace Microsoft::WRL;
    auto device = EasyEngine::getRenderingManager()->getDevice();

    // スワップチェインの作成
    ComPtr<IDXGIFactory> factory;
    HRESULT hr = CreateDXGIFactory( IID_PPV_ARGS(&factory) );
    if( FAILED(hr) ) return false;
    DXGI_SWAP_CHAIN_DESC sc_desc{};
    sc_desc.BufferCount = 1;
    sc_desc.BufferDesc.Width = kHorizontalResolution<UINT>;
    sc_desc.BufferDesc.Height = kVerticalResolution<UINT>;
    sc_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sc_desc.BufferDesc.RefreshRate.Numerator = 60;
    sc_desc.BufferDesc.RefreshRate.Denominator = 1;
    sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc_desc.OutputWindow = EasyEngine::getWindowHandle();
    sc_desc.SampleDesc.Count = 1;
    sc_desc.SampleDesc.Quality = 0;
    sc_desc.Windowed = true;
    sc_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    hr = factory->CreateSwapChain( device.Get(), &sc_desc, &sc_ );
    if( FAILED(hr) ) return false;

    // 描画ターゲット作成
    ComPtr<ID3D11Texture2D> backbuffer;
    hr = sc_->GetBuffer( 0, _uuidof(ID3D11Texture2D), &backbuffer );
    if( FAILED(hr) ) return false;
    hr = device->CreateRenderTargetView( backbuffer.Get(), nullptr, &rtv_ );
    if( FAILED(hr) ) return false;

    // ビューポート設定
    viewport_.TopLeftX = 0.0F;
    viewport_.TopLeftY = 0.0F;
    viewport_.Width = kHorizontalResolution<float>;
    viewport_.Height = kVerticalResolution<float>;
    viewport_.MinDepth = 0.0F;
    viewport_.MaxDepth = 1.0F;


    task_.setJob( this, &Test2DLevel::update );
    EasyEngine::getTaskManager()->registerJob( &task_ );

    if( !scene_.initialize( EasyEngine::getRenderingManager()) )
        return false;

    if( !actor_.initialize() )
        return false;

    return true;
}

void Test2DLevel::finalize()
{
    actor_.finalize();
    scene_.finalize();
}

void Test2DLevel::update( uint64_t )
{
    float color[4] = { 1.0F, 1.0F, 1.0F, 1.0F };
    EasyEngine::getRenderingManager()->getImmediateContext()->ClearRenderTargetView(
        rtv_.Get(), color );
    scene_.prepare();

    scene_.entry( &actor_ );

    scene_.render(
        EasyEngine::getRenderingManager()->getImmediateContext().Get(),
        {rtv_.Get()},
        {viewport_},
        {}
    );

    sc_->Present( 0, 0 );
}

// EOF
