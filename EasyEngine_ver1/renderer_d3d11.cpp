// 作成者 : 板場
#include "renderer_d3d11.hpp"
#include "vertex_shader_d3d11.hpp"
#include "geometry_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"
#include "texture_d3d11.hpp"

namespace
{
    constexpr int kBlendModeNum = 3;

    // サンプラーステート
    constexpr D3D11_SAMPLER_DESC kSamplerDesc =
    {
        D3D11_FILTER_MIN_MAG_MIP_LINEAR,        // Filter
        D3D11_TEXTURE_ADDRESS_BORDER,           // AddressU
        D3D11_TEXTURE_ADDRESS_BORDER,           // AddressV
        D3D11_TEXTURE_ADDRESS_BORDER,           // AddressW
        0,                                      // MipLODBias
        0,                                      // MaxAnisotropy
        static_cast<D3D11_COMPARISON_FUNC>(0),  // ComparisonFunc
        {0,0,0,0},                              // BorderColor
        0,                                      // MinLOD
        0                                       // MaxLOD
    };

    // ブレンドステート
    constexpr D3D11_RENDER_TARGET_BLEND_DESC kRenderTargetBlendDesc[] =
    {
        { // BlendMode 「Normal」
            true,                           // BlendEnable
            D3D11_BLEND_SRC_ALPHA,          // SrcBlend
            D3D11_BLEND_INV_SRC_ALPHA,      // DestBlend
            D3D11_BLEND_OP_ADD,             // BlendOp
            D3D11_BLEND_ONE,                // SrcBlendAlpha
            D3D11_BLEND_ZERO,               // DestBlendAlpha
            D3D11_BLEND_OP_ADD,             // BlendOpAlpha
            D3D11_COLOR_WRITE_ENABLE_ALL    // RenderTargetWriteMask
        },
        { // BlendMode 「Additive」
            true,
            D3D11_BLEND_ONE,
            D3D11_BLEND_ONE,
            D3D11_BLEND_OP_ADD,
            D3D11_BLEND_ONE,
            D3D11_BLEND_ZERO,
            D3D11_BLEND_OP_ADD,
            D3D11_COLOR_WRITE_ENABLE_ALL
        },
        { // BlendMode 「Subtraction」
            true,
            D3D11_BLEND_ONE,
            D3D11_BLEND_ONE,
            D3D11_BLEND_OP_SUBTRACT,
            D3D11_BLEND_ONE,
            D3D11_BLEND_ZERO,
            D3D11_BLEND_OP_ADD,
            D3D11_COLOR_WRITE_ENABLE_ALL
        },
    };

} // !unnamed namespace

BEGIN_EGEG
// RendererD3D11
/*===========================================================================*/
// コンストラクタ
RendererD3D11::RendererD3D11( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain ) :
    p_device_( pDevice ),
    p_immediate_context_( pImmediateContext ),
    p_swap_chain_( pSwapChain )
{
    p_device_->AddRef();
    p_immediate_context_->AddRef();
    p_swap_chain_->AddRef();
}

// デストラクタ
RendererD3D11::~RendererD3D11()
{
    for( int i = 0; i < ::kBlendModeNum; ++i )
        p_blend_states_[i]->Release();
    p_sampler_state_->Release();
    p_render_target_view_->Release();
    p_swap_chain_->Release();
    p_immediate_context_->Release();
    p_device_->Release();
}

// 初期化
bool RendererD3D11::initialize()
{
    // パイプラインにレンダーターゲットビューを設定
    ID3D11Texture2D* backbuffer;
    if (FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer)))
    {
        return false;
    }
    if (FAILED(p_device_->CreateRenderTargetView(backbuffer, nullptr, &p_render_target_view_)))
    {
        backbuffer->Release();
        return false;
    }
    p_immediate_context_->OMSetRenderTargets(1U, &p_render_target_view_, nullptr);

    // パイプラインにビューポートを設定
    D3D11_TEXTURE2D_DESC desc;
    backbuffer->GetDesc(&desc);
    viewport_.TopLeftX = viewport_.TopLeftY = 0.0F;
    viewport_.Width = static_cast<float>(desc.Width);
    viewport_.Height = static_cast<float>(desc.Height);
    viewport_.MinDepth = 0.0F;
    viewport_.MaxDepth = 1.0F;
    p_immediate_context_->RSSetViewports(1U, &viewport_);

    // 不要になったバッファを開放
    backbuffer->Release();

    // サンプラーステートを生成
    if( FAILED(p_device_->CreateSamplerState(&::kSamplerDesc, &p_sampler_state_)) )
        return false;

    // ブレンドステートを生成
    for( int i = 0; i < 3; ++i )
    {
        D3D11_BLEND_DESC desc =
        {
            false,
            false,
            ::kRenderTargetBlendDesc[i]
        };
        if( FAILED(p_device_->CreateBlendState(&desc, &p_blend_states_[i])) )
            return false;
    }

    return true;
}

// 画面クリア
void RendererD3D11::clear( const Vector4D& Color )
{
    float color[] = { Color.x, Color.y, Color.z, Color.w };
    p_immediate_context_->ClearRenderTargetView( p_render_target_view_, color );
}

// モデル描画
void RendererD3D11::renderModel( const Model& Model, BlendMode Mode )
{
    // 頂点バッファ作成
    /*const D3D11_BUFFER_DESC kVertexBufferDesc =
    {
        sizeof(VertexData)* Model.mesh.vertices.size(),
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_VERTEX_BUFFER,
        0,
        0,
        0
    };
    const D3D11_SUBRESOURCE_DATA kVertexSubResourceData =
    {
        Model.mesh.vertices.data(),
        0U,
        0U
    };
    ID3D11Buffer* p_vertexbuffer;
    if( FAILED(p_device_->CreateBuffer(&kVertexBufferDesc, &kVertexSubResourceData, &p_vertexbuffer)) )
    {
        p_blendstate->Release();   
        return;
    }*/

    // インデックスバッファ作成
    //std::vector<UINT> indices;
    //indices.reserve( Model.mesh.indices.size() * 3U );  // 頂点インデックス * 3頂点
    //// 頂点インデックスを一つの配列にまとめる
    //for( const auto& polygon : Model.mesh.indices )
    //{
    //    for( int i = 0; i < 3; ++i )
    //        indices.push_back( polygon.index[i] );
    //}

    //const D3D11_BUFFER_DESC kIndexBufferDesc =
    //{
    //    sizeof(UINT) * indices.size(),
    //    D3D11_USAGE_DEFAULT,
    //    D3D11_BIND_INDEX_BUFFER,
    //    0,
    //    0,
    //    0
    //};
    //const D3D11_SUBRESOURCE_DATA kIndexSubResourceData =
    //{
    //    indices.data(),
    //    0U,
    //    0U,
    //};
    //ID3D11Buffer* p_indexbuffer;
    //if( FAILED(p_device_->CreateBuffer(&kIndexBufferDesc, &kIndexSubResourceData, &p_indexbuffer)) )
    //{
    //    p_blendstate->Release();
    //    p_vertexbuffer->Release();
    //    return;
    //}

    // モデルからステート情報を取得
    ID3D11InputLayout *p_inputlayout = nullptr;
    ID3D11VertexShader* p_vertexshader = nullptr;
    ID3D11GeometryShader* p_geometryshader = nullptr;
    ID3D11PixelShader* p_pixelshader = nullptr;
    ID3D11ShaderResourceView* p_shaderresourceview = nullptr;
    if( Model.vertex_shader )
    {
        p_inputlayout = static_cast<VertexShaderD3D11*>(Model.vertex_shader)->getLayout();
        p_vertexshader = static_cast<VertexShaderD3D11*>(Model.vertex_shader)->getShader();
    }
    if( Model.geometry_shader )
    {
        p_geometryshader = static_cast<GeometryShaderD3D11*>(Model.geometry_shader)->getShader();
    }
    if( Model.pixel_shader )
    {
        p_pixelshader = static_cast<PixelShaderD3D11*>(Model.pixel_shader)->getShader();

        if( Model.texture )
        {
            p_shaderresourceview = static_cast<TextureD3D11*>(Model.texture)->getShaderResourceView();
        }
    }

    // パイプラインステートを設定
    //p_immediate_context_->IASetInputLayout( p_inputlayout );
    //size_t size = sizeof VertexData;
    //unsigned offset = 0U;
    //p_immediate_context_->IASetVertexBuffers( 0, 1, &p_vertexbuffer, &size, &offset );
    //p_immediate_context_->IASetIndexBuffer( p_indexbuffer, DXGI_FORMAT_R32_UINT, 0 );
    //p_immediate_context_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
    //if( p_vertexshader ) p_immediate_context_->VSSetShader( p_vertexshader, nullptr, 0U );
    //if( p_geometryshader ) p_immediate_context_->GSSetShader( p_geometryshader, nullptr, 0U );
    //if( p_pixelshader )
    //{
    //    p_immediate_context_->PSSetShader( p_pixelshader, nullptr, 0U );
    //    p_immediate_context_->PSSetSamplers( 0, 1, &p_sampler_state_ );
    //    p_immediate_context_->PSSetShaderResources( 0, 1, &p_shaderresourceview );
    //}
    p_immediate_context_->OMSetBlendState( p_blend_states_[Mode], nullptr, 0xFFFFFFFF );

    //// 描画
    //p_immediate_context_->DrawIndexed( indices.size(), 0, 0 );

    // 不要になったインターフェイスの解放
    if( p_shaderresourceview )  p_shaderresourceview->Release();
    if( p_pixelshader )         p_pixelshader->Release();
    if( p_geometryshader )      p_geometryshader->Release();
    if( p_vertexshader )        p_vertexshader->Release();
    if( p_inputlayout )         p_inputlayout->Release();
    //p_indexbuffer->Release();
    //p_vertexbuffer->Release();
    //p_blendstate->Release();
}
END_EGEG
// EOF
