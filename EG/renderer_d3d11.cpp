// 作成者 : 板場
#include "renderer_d3d11.hpp"
#include <fstream>
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

// RendererD3D11内部で使用するクラスの定義
BEGIN_EG_EG
class RendererD3D11Child
{
public :
    RendererD3D11Child( RendererD3D11* pOwner ) :
        p_owner_( pOwner )
    {}
    virtual ~RendererD3D11Child()
    {
     //   p_owner_->notifyRelease( this );
    }

private :
    RendererD3D11* p_owner_;
};

class TextureD3D11 : public ITexture
{
public :
    TextureD3D11( RendererD3D11* pOwner ) :
        p_owner_( pOwner )
    {}

    void addRef() override { ++ref_cnt_; }
    void release() override
    {
        if( --ref_cnt_ <= 0 )
        {
            p_owner_->notifyRelease( this );
            p_resource_->Release();
            delete this;
        }
    }

    void set( ID3D11ShaderResourceView* pSRV ) { p_resource_ = pSRV; }
    ID3D11ShaderResourceView* get() const { return p_resource_; }

private :
    unsigned ref_cnt_ = 0;
    RendererD3D11* p_owner_ = nullptr;
    ID3D11ShaderResourceView* p_resource_ = nullptr;
};
class VertexShaderD3D11 : public IVertexShader
{
public :
    VertexShaderD3D11( RendererD3D11* pOwner ) :
        p_owner_( pOwner )
    {}

    void addRef() override { ++ref_cnt_; }
    void release() override 
    {
        if( --ref_cnt_ <= 0 )
        {
            p_owner_->notifyRelease( this );
            p_vertex_shader_->Release();
            delete this;
        }
    }

    void set( ID3D11VertexShader* pVS ) { p_vertex_shader_ = pVS; }
    ID3D11VertexShader* get() const { return p_vertex_shader_; }

private :
    unsigned ref_cnt_ = 0;
    RendererD3D11* p_owner_ = nullptr;
    ID3D11VertexShader* p_vertex_shader_ = nullptr;
};
class PixelShaderD3D11 : public IPixelShader
{
public :
    PixelShaderD3D11( RendererD3D11* pOwner ) :
        p_owner_( pOwner )
    {}

    void addRef() override { ++ref_cnt_; }
    void release() override
    {
        if( --ref_cnt_ <= 0 )
        {
            p_owner_->notifyRelease( this );
            p_pixel_shader_->Release();
            delete this;
        }
    }

    void set( ID3D11PixelShader* pPS ) { p_pixel_shader_ = pPS; }
    ID3D11PixelShader* get() const { return p_pixel_shader_; }

private :
    unsigned ref_cnt_ = 0;
    RendererD3D11* p_owner_ = nullptr;
    ID3D11PixelShader* p_pixel_shader_ = nullptr;
};
END_EG_EG // RendererD3D11内部で使用するクラスの定義

// unnamed namespace
/*===========================================================================*/
namespace
{
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC*, HWND, UINT, UINT );
    void setViewportDesc( D3D11_VIEWPORT*, float, float );
    template<typename Interface> void safeRelease( Interface*& );

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

// 破棄
void RendererD3D11::release()
{
    if( --ref_cnt_ <= 0 )
    {
        finalize();
        delete this;
    }
}

// テクスチャのロード
bool RendererD3D11::loadTexture( const wchar_t* FilePath, ITexture** ppOut )
{
    using namespace DirectX;

    auto find = textures_.find( FilePath );

    // キャッシュにある場合
    if( find != textures_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // ファイルからデータを読み込む
        TexMetadata mdata;
        ScratchImage image;
        if( FAILED(LoadFromWICFile(FilePath, 0, &mdata, image)) )
            return false;

        // ビューを作成
        ID3D11ShaderResourceView* view;
        if( FAILED(CreateShaderResourceViewEx(
            p_device_,
            image.GetImages(),
            image.GetImageCount(),
            mdata,
            D3D11_USAGE_DEFAULT,
            D3D11_BIND_SHADER_RESOURCE,
            0,
            0,
            false,
            &view)) )
            return false;

        TextureD3D11* p_tex = new TextureD3D11( this );
        p_tex->set( view );
        p_tex->addRef();
        *ppOut = p_tex;
    }

    return true;
}

// 頂点シェーダのロード
bool RendererD3D11::loadVertexShader( const char* FilePath, IVertexShader** ppOut )
{
    auto find = vertex_shaderes_.find( FilePath );

    // キャッシュにある場合
    if( find != vertex_shaderes_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        std::fstream stream( FilePath, std::ios::binary | std::ios::in );
        if( stream.is_open() == false )
            return false;

        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        UINT size = static_cast<UINT>(end - beg);
        char* blob = new char [size];
        stream.read( blob, size );
        stream.close();

        VertexShaderD3D11* p_vs = new VertexShaderD3D11( this );
        ID3D11VertexShader* p_d3dvs;
        if( FAILED(p_device_->CreateVertexShader(blob, size, nullptr, &p_d3dvs)) )
            return false;

        p_vs->set( p_d3dvs );
        p_vs->addRef();
        *ppOut = p_vs;
    }

    return true;
}

// ピクセルシェーダのロード
bool RendererD3D11::loadPixelShader( const char* FilePath, IPixelShader** ppOut )
{
    auto find = pixel_shaderes_.find( FilePath );

    // キャッシュにある場合
    if( find != pixel_shaderes_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        std::fstream stream(FilePath, std::ios::binary | std::ios::in);
        if (stream.is_open() == false)
            return false;

        stream.seekg(0, std::ios::end);
        auto end = stream.tellg();
        stream.clear();
        stream.seekg(0, std::ios::beg);
        auto beg = stream.tellg();
        UINT size = static_cast<UINT>(end - beg);
        char* blob = new char[size];
        stream.read(blob, size);
        stream.close();

        PixelShaderD3D11* p_ps = new PixelShaderD3D11(this);
        ID3D11PixelShader* p_d3dps;
        if (FAILED(p_device_->CreatePixelShader(blob, size, nullptr, &p_d3dps)))
            return false;

        p_ps->set(p_d3dps);
        p_ps->addRef();
        *ppOut = p_ps;
    }

    return true;
}

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

// テクスチャ開放メッセージの受け取り
// 通知者がキャッシュに存在したら、キャッシュから抜き出す
//
// in pNotifier : 開放を知らせるテクスチャリソース
void RendererD3D11::notifyRelease( ITexture* pNotifier )
{
    for( auto itr = textures_.begin(), end = textures_.end();
        itr != end; ++itr )
    {
        if( itr->second == pNotifier )
        {
            textures_.erase( itr->first );
            break;
        }
    }
}
// 頂点シェーダ開放メッセージの受け取り
// 通知者がキャッシュに存在したら、キャッシュから抜き出す
//
// in pNotifier : 開放を知らせる頂点シェーダ
//
void RendererD3D11::notifyRelease( IVertexShader* pNotifier )
{
    for( auto itr = vertex_shaderes_.begin(), end = vertex_shaderes_.end();
        itr != end; ++itr )
    {
        if( itr->second == pNotifier )
        {
            vertex_shaderes_.erase( itr->first );
            break;
        }
    }
}
//
// ピクセルシェーダ開放メッセージの受け取り
// 通知者がキャッシュに存在したら、キャッシュから抜き出す
//
// in pNotifier
//
void RendererD3D11::notifyRelease( IPixelShader* pNotifier )
{
    for( auto itr = pixel_shaderes_.begin(), end = pixel_shaderes_.end();
        itr != end; ++itr )
    {
        if( itr->second == pNotifier )
        {
            pixel_shaderes_.erase( itr->first );
            break;
        }
    }
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
