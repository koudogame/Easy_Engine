///
/// @file   renderer_d3d11.hpp
/// @author 板場
///
/// @brief  Direct3D11を使用したレンダラーです。<br>
///         RendererFactoryにより生成されます。
///
///
#ifndef INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#define INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#include <unordered_map>
#include <Windows.h>
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EG_EG
class RendererD3D11 :
    public IRenderer
{
public :
    static IRenderer* create();

    void addRef() override { ++ref_cnt_; }
    void release() override;
    void beginRender( float* ) override;
    void setVertexShader( IVertexShader* ) override;
    void setPixelShader( IPixelShader* ) override;
    void setTexture( ITexture* ) override;
    void render( const Mesh& ) override;
    void endRender() override;


    void notifyRelease( ITexture* );        ///< テクスチャの解放通知を受け取ります。
    void notifyRelease( IVertexShader* );   ///< 頂点シェーダーの解放通知を受け取ります。
    void notifyRelease( IPixelShader* );    ///<  ピクセルシェーダーの解放通知を受け取ります。
private :
    bool initialize();  /// 初期化処理 * 生成時に呼び出されます。
    ~RendererD3D11();

    unsigned ref_cnt_ = 0;  /// 参照数カウント

    HWND                    window_handle_;                     /// 出力ターゲットウィンドウハンドル
    D3D_FEATURE_LEVEL       feature_level_;                     /// D3D機能レベル
    ID3D11Device*           p_device_ = nullptr;                /// D3Dデバイスインターフェイス
    ID3D11DeviceContext*    p_immediate_context_ = nullptr;     /// D3Dデバイスコンテキストインターフェイス
    IDXGISwapChain*         p_swap_chain_ = nullptr;            /// DXGIスワップチェインインターフェス
    ID3D11RenderTargetView* p_render_target_view_ = nullptr;    /// D3D描画ターゲットビューインターフェイス

    std::unordered_map<const wchar_t*, ITexture*> textures_;            /// テクスチャキャッシュ
    std::unordered_map<const char*, IVertexShader*> vertex_shaderes_;   /// 頂点シェーダキャッシュ
    std::unordered_map<const char*, IPixelShader*> pixel_shaderes_;     /// ピクセルシェーダキャッシュ
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
/// EOF
