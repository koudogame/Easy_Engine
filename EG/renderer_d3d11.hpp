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
    // 初期化済みのインターフェイスを返却します。
    static IRenderer* create();

    //bool loadResource( const wchar_t FilePath[], Texture* pOut ) override;
    //void unloadResource( Texture* pTexture ) override;
    //bool loadVertexShader( const char FilePath[], IShader* pOut ) override;
    //bool loadPixelShader( const char FilePath[], IShader* pOut ) override;
    //void unloadShader( IShader* pOut );

    void clear( float R = 1.0F, float G = 1.0F, float B = 1.0F, float A = 1.0F ) override;
    void render( const Model& Object ) override;

private :
    bool initialize();
    void finalize();

    unsigned referenced_num_ = 0;

    HWND                    window_handle_;
    D3D_FEATURE_LEVEL       feature_level_;
    ID3D11Device*           p_device_ = nullptr;
    ID3D11DeviceContext*    p_immediate_context_ = nullptr;
    IDXGISwapChain*         p_swap_chain_ = nullptr;
    ID3D11RenderTargetView* p_render_target_view_ = nullptr;

    std::unordered_map<const wchar_t*, ID3D11ShaderResourceView*> textures_;
    std::unordered_map<const char*, ID3D11VertexShader*> vertex_shaderes_;
    std::unordered_map<const char*, ID3D11PixelShader*> pixel_shaderes_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
// EOF
