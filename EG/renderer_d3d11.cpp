// 作成者 : 板場
#include "renderer_d3d11.hpp"
#include "DirectXTex/DirectXTex.h"
#include "renderer_factory.hpp"

#pragma comment( lib, "d3d11.lib" )

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif

// レンダラーファクトリにRendererD3D11を登録
ADD_RENDERER( EG_EG RendererID::kDirect3D11, &RendererD3D11::create )


// unnamed namespace
/*===========================================================================*/
namespace
{
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC*, HWND, UINT, UINT );
    void setViewportDesc( D3D11_VIEWPORT*, float, float );
    template<typename Interface> void safeRelease( Interface*& );

    bool loadBinary( const char*, char*, long* );

#ifdef _DEBUG
    constexpr UINT kD3D11CreateFlags = 0;
#else
    constexpr UINT kD3D11CreateFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

    constexpr D3D_FEATURE_LEVEL kFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
} // unnamed namespace

BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// 生成
IRenderer* RendererD3D11::create()
{
    RendererD3D11* p =  new(std::nothrow) RendererD3D11();
    return p;
}
//
//// テクスチャリソースのロード
//// 同一リソースはコピーする。
//bool RendererD3D11::loadResource( const wchar_t FilePath[], Texture* pOut )
//{
//    using namespace DirectX;
//
//    auto find = textures_.find( FilePath );
//
//    // 既に読み込まれている場合
//    if( find != textures_.end() )
//    {
//        find->second->AddRef();
//        pOut->setResource( find->second );
//    }
//    // 新規呼び込みの場合
//    else
//    {
//        // ファイルからデータを読み込む
//        TexMetadata mdata;
//        ScratchImage image;
//        if( FAILED(LoadFromWICFile(FilePath, 0, &mdata, image)) )
//            return false;
//
//        // ビューを作成
//        ID3D11ShaderResourceView* view;
//        if( FAILED(CreateShaderResourceViewEx(
//            p_device_,
//            image.GetImages(),
//            image.GetImageCount(),
//            mdata,
//            D3D11_USAGE_DEFAULT,
//            D3D11_BIND_SHADER_RESOURCE,
//            0,
//            0,
//            false,
//            &view)) )
//            return false;
//
//        textures_.insert( std::make_pair(FilePath, view) );
//    }
//
//    return true;
//}
//// テクスチャリソースのアンロード
//void RendererD3D11::unloadResource( Texture* pOut )
//{
//    static_cast<ID3D11ShaderResourceView*>( pOut->getResource() )->Release();
//    pOut->setResource( nullptr );
//}
//
//// シェーダーのロード
//// 同一シェーダーはコピーする。
//bool RendererD3D11::loadVertexShader( const char FilePath[], IShader* pOut )
//{ 
//    if( pOut->getID() != ShaderID::kVertexShader ) 
//        return false;
//
//    char* blob;
//    long  length;
//    ::loadBinary( FilePath, blob, &length );
//
//    ID3D11VertexShader* shader;
//    if( FAILED(p_device_->CreateVertexShader(blob, length, nullptr, &shader)) )
//    {
//        delete blob;
//        return false;
//    }
//
//    return true;
//}
//bool RendererD3D11::loadPixelShader( const char FilePath[], IShader* pOut )
//{
//
//
//    return true;
//}
//// シェーダ―のアンロード
//void RendererD3D11::unloadShader( IShader* pShader )
//{
//
//
//}


// 初期化処理
bool RendererD3D11::initialize()
{
    HWND this_window = FindWindow( "Game_Abyabyabyabyabya", nullptr );

    // ウィンドウ領域の取得
    RECT region;
    if( GetClientRect( this_window, &region ) == false )
        return false;
    const long kRegionWidth = region.right;         // ウィンドウ領域幅
    const long kRegionHeight = region.bottom;       // ウィンドウ領域高さ

    // D3DデバイスとDXGIスワップチェインの作成
    DXGI_SWAP_CHAIN_DESC sc_desc = {};
    ::setSwapChainDesc( &sc_desc, this_window, (UINT)kRegionWidth, (UINT)kRegionHeight );
    if( FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        ::kD3D11CreateFlags,
        ::kFeatureLevels,
        sizeof(::kFeatureLevels) / sizeof(D3D_FEATURE_LEVEL),
        D3D11_SDK_VERSION,
        &sc_desc,
        &p_swap_chain_,
        &p_device_,
        &feature_level_,
        &p_immediate_context_)) )
        return false;

    // 描画ターゲットをパイプラインに設定
    ID3D11Texture2D* buffer;
    if( FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer)) )
        return false;
    if( FAILED(p_device_->CreateRenderTargetView(buffer, nullptr, &p_render_target_view_)) )
    {
        buffer->Release();
        return false;
    }
    p_immediate_context_->OMSetRenderTargets( 1, &p_render_target_view_, nullptr );

    // ビューポートをパイプラインに設定
    D3D11_VIEWPORT vp = {};
    ::setViewportDesc( &vp, (float)kRegionWidth, (float)kRegionHeight );
    p_immediate_context_->RSSetViewports( 1, &vp );

    return true;
}
// 終了処理
void RendererD3D11::finalize()
{
    // フルスクリーンモードを解除
    if( p_swap_chain_ )
        p_swap_chain_->SetFullscreenState( false, nullptr );

    // パイプラインのステート設定をクリア
    if( p_immediate_context_ )
        p_immediate_context_->ClearState();

    // 各種インターフェイスを解放
    ::safeRelease( p_render_target_view_ );
    ::safeRelease( p_swap_chain_ );
    ::safeRelease( p_immediate_context_ );
    ::safeRelease( p_device_ );
}

// 描画開始
void RendererD3D11::beginRender(float* Color )
{
    p_immediate_context_->ClearRenderTargetView( p_render_target_view_, Color );
}
// モデルの描画
void RendererD3D11::render(const Mesh& Object)
{

}
// 描画終了
void RendererD3D11::endRender()
{
    p_swap_chain_->Present(0, 0);
}
END_EG_EG

// unnamed namespace
/*===========================================================================*/
namespace
{
    // スワップチェインの定義を設定
    //
    // in pOut   : 出力用構造体のアドレス
    // in hWnd   : 描画先ウィンドウハンドル
    // in Width  : バックバッファ幅
    // in Height : バックバッファ高さ
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC* pOut, HWND hWnd, UINT Width, UINT Height )
    {
        pOut->BufferCount = 1;
        pOut->BufferDesc.Width = Width;
        pOut->BufferDesc.Height = Height;
        pOut->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        pOut->BufferDesc.RefreshRate.Numerator = 60;
        pOut->BufferDesc.RefreshRate.Denominator = 1;
        pOut->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        pOut->OutputWindow = hWnd;
        pOut->SampleDesc.Count = 1;
        pOut->SampleDesc.Quality = 0;
        pOut->Windowed = true;
        pOut->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    }
    
    // ビューポートの定義を設定
    //
    // in pOut   : 出力用構造体のアドレス
    // in Width  : ビューポート幅
    // in Height : ビューポート高さ
    void setViewportDesc( D3D11_VIEWPORT* pOut, float Width, float Height )
    {
        pOut->Width = Width;
        pOut->Height = Height;
        pOut->MinDepth = 0.0F;
        pOut->MaxDepth = 1.0F;
    }

    // D3Dインターフェイスの安全な解放
    //
    // <in> D3D : 解放するインターフェイスの型
    //
    // in pInterface
    template <typename Interface>
    void safeRelease( Interface*& Interface )
    {
        if( Interface )
        {
            Interface->Release();
            Interface = nullptr;
        }
    }
} // unnamed namespace
// EOF
