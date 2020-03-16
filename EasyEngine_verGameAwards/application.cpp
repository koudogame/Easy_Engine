// 作成者 : 板場
#include "application.hpp"
#include <chrono>
#include <tchar.h>
#include <Windows.h>
#include <wrl.h>
#include <dxgi.h>
#include <d3d11.h>
#include "application_status.hpp"
#include "easy_engine.hpp"

#include "shader_loader.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
#include "actor3d.hpp"
#include "rendering3d_component.hpp"
#include "scene3d.hpp"

#pragma comment( lib, "dxgi.lib" )

// ウィンドウプロシージャ関数宣言
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEX = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace


BEGIN_EGEG
 class TestActor :
    public Actor3D
{
public :
    TestActor() :
        Actor3D( UID<TestActor>() )
    {}

    bool initialize() override { return true; }
    void finalize() override {}
};
class TestVS :
    public VertexShader
{
public :
    static constexpr D3D11_INPUT_ELEMENT_DESC kInputElementDescs[] =
    {
        {
            kVertexPositionSemantic,
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
    };
    static constexpr const char* kVSFileName = "test_vs.cso";

    TestVS( ID3D11VertexShader* VS, ID3D11InputLayout* IL ) :
        VertexShader( VS, IL )
    {}

    VertexBinder getVertexBinder() const override
    {
        return VertexBinder( "POSITION" );
    }

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetShader( shader_.Get(), nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetShaderResources( 0, 0, nullptr );
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetConstantBuffers( 0, 0, nullptr );
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetSamplers( 0, 0, nullptr );
    }
};
class TestGS :
    public GeometryShader
{
public :
    TestGS( ID3D11GeometryShader* GS ) :
        GeometryShader( GS )
    {}

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetShader( nullptr, nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetShaderResources( 0, 0, nullptr );
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetConstantBuffers( 0, 0, nullptr );
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetSamplers( 0, 0, nullptr );
    }
};
class TestPS :
    public PixelShader
{
public :
    static constexpr const char* kPSFileName = "test_ps.cso";

    TestPS( ID3D11PixelShader* PS ) :
        PixelShader( PS )
    {}

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetShader( shader_.Get(), nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetShaderResources( 0, 0, nullptr );
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetConstantBuffers( 0, 0, nullptr );
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetSamplers( 0, 0, nullptr );
    }
};

// Application 関数定義
/*===========================================================================*/
// 実行
void Application::run()
{
    if( EasyEngine::initialize() == false ) return;
    mainloop();
    EasyEngine::finalize();
}

// メインループ
template <class Ty>
using ComPtr = Microsoft::WRL::ComPtr<Ty>;
void Application::mainloop()
{
    using namespace std::chrono;

    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;
   
    ComPtr<IDXGIFactory> factory;
    HRESULT hr = CreateDXGIFactory( IID_PPV_ARGS(&factory) );
    if( FAILED(hr) )    return;

    ComPtr<IDXGISwapChain> sc;
    DXGI_SWAP_CHAIN_DESC sc_desc {};
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
    hr = factory->CreateSwapChain(
        EasyEngine::getRenderingEngine()->getDevice().Get(),
        &sc_desc,
        &sc
    );
    if( FAILED(hr) ) _asm int 3;
    ComPtr<ID3D11Texture2D> back_buffer = nullptr;
    hr = sc->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**)&back_buffer
    );
    if( FAILED(hr) ) _asm int 3;
    ComPtr<ID3D11RenderTargetView> render_target;
    EasyEngine::getRenderingEngine()->getDevice()->
    CreateRenderTargetView(
        back_buffer.Get(),
        nullptr,
        &render_target
    );


    D3D11_BUFFER_DESC bf_desc {};
    bf_desc.Usage = D3D11_USAGE_DEFAULT;
    bf_desc.ByteWidth = sizeof( VertexPositionType ) * 4;
    bf_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    VertexPositionType pos[] =
    {
        { -1.0F, 1.0F, 0.0F },
        {  0.0F, 1.0F, 0.0F },
        { -1.0F, 0.0F, 0.0F },
        {  0.0F, 0.0F, 0.0F }
    };
    D3D11_SUBRESOURCE_DATA v_srd {};
    v_srd.pSysMem = pos;
    ComPtr<ID3D11Buffer> buffer;
    EasyEngine::getRenderingEngine()->getDevice()->
    CreateBuffer(
        &bf_desc,
        &v_srd,
        &buffer
    );

    ComPtr<ID3D11Buffer> idx_buffer;
    D3D11_BUFFER_DESC idx_desc {};
    idx_desc.Usage = D3D11_USAGE_DEFAULT;
    idx_desc.ByteWidth = sizeof( UINT ) * 6;
    idx_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    UINT index[] =
    {
        0,1,2,
        1,3,2
    };
    D3D11_SUBRESOURCE_DATA v_idx {};
    v_idx.pSysMem = index;
    EasyEngine::getRenderingEngine()->getDevice()->
    CreateBuffer(
        &idx_desc,
        &v_idx,
        &idx_buffer
    );
    ShaderLoader loader{ EasyEngine::getRenderingEngine()->getDevice() };
    auto vs = loader.createVertexShader<TestVS>();
    auto ps = loader.createPixelShader<TestPS>();


    Model<TestVS, TestGS, TestPS> model;
    model.vertex_shader = std::move(vs);
    model.pixel_shader = std::move(ps);
    model.vertex_data.setNumVertices( getArraySize(index) );
    model.vertex_data.setVertexBuffer( kVertexPositionSemantic, buffer.Get() );
    model.vertex_data.setIndexBuffer( idx_buffer.Get() );
    
    TestActor test;
    auto component = test.addComponent<Rendering3DComponent>();
    component->setModel( model );


    EasyEngine::getRenderingEngine()->getImmediateContext();
    Scene3D scene{ EasyEngine::getRenderingEngine()->getImmediateContext() };
    scene.entry( &test );

    MSG msg{};
    while( msg.message != WM_QUIT )
    {
        // メッセージ処理
        if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // ゲーム処理
        else
        {
            // フレームレート制御
            curr_time = high_resolution_clock::now();
            auto erapsed_time = curr_time - last_time;
            if( duration_cast<microseconds>(erapsed_time).count() >= TimePerFrame<>::value )
            {
                last_time = curr_time;
                
                scene.entry( &test );

                float backcolor[4] = { 1.0F, 1.0F, 1.0F, 1.0F };
                EasyEngine::getRenderingEngine()->getImmediateContext()->
                ClearRenderTargetView(
                    render_target.Get(),
                    backcolor
                );
                scene.render(
                    {render_target.Get()},
                    {{
                        0.0F,
                        0.0F,
                        kHorizontalResolution<float>,
                        kVerticalResolution<float>,
                        0.0F,
                        1.0F
                    }},
                    {}
                );

                
                sc->Present(0,0);
            }
        }
    }
}

END_EGEG
// EOF
