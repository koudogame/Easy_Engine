#ifndef INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#define INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
// 作成者 : 板場
#include <unordered_map>
#include <Windows.h>
#include <d3d11.h>
#include "renderer.hpp"

BEGIN_EG_EG
//
// Direct3D11用レンダラー
// RendererFactoryによって生成されます。
//
class RendererD3D11 :
    public IRenderer
{
public :
    // インターフェイスの生成処理。
    static IRenderer* create();

    void addRef() override { ++ref_cnt_; }
    void release() override;

    bool loadTexture( const wchar_t*, ITexture** ) override;
    bool loadVertexShader( const char*, IVertexShader** ) override;
    bool loadPixelShader( const char*, IPixelShader** ) override;
    void beginRender( float* ) override;
    void setVertexShader( IVertexShader* ) override;
    void setPixelShader( IPixelShader* ) override;
    void setTexture( ITexture* ) override;
    void render( const Mesh& ) override;
    void endRender() override;


    void notifyRelease( ITexture* );
    void notifyRelease( IVertexShader* );
    void notifyRelease( IPixelShader* );
private :
    bool initialize();
    void finalize();

    unsigned ref_cnt_ = 0;

    HWND                    window_handle_;
    D3D_FEATURE_LEVEL       feature_level_;
    ID3D11Device*           p_device_ = nullptr;
    ID3D11DeviceContext*    p_immediate_context_ = nullptr;
    IDXGISwapChain*         p_swap_chain_ = nullptr;
    ID3D11RenderTargetView* p_render_target_view_ = nullptr;

    std::unordered_map<const wchar_t*, ITexture*> textures_;
    std::unordered_map<const char*, IVertexShader*> vertex_shaderes_;
    std::unordered_map<const char*, IPixelShader*> pixel_shaderes_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
// EOF
