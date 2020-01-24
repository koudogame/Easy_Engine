// �쐬�� : ��
#include "renderer_d3d11.hpp"

namespace
{
    // ���_�f�[�^���̓��C�A�E�g
    constexpr D3D11_INPUT_ELEMENT_DESC kVertexInputLayout[] =
    {
        {
            "POSITION",                     // SemanticName
            0,                              // SemanticIndex
            DXGI_FORMAT_R32G32B32_FLOAT,    // Format
            0,                              // InputSlot
            0,                              // AlignedByteOffset
            D3D11_INPUT_PER_VERTEX_DATA,    // InputSlotClass
            0                               // InstanceDataRate
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            0,
            (UINT) sizeof( EGEG Float3 ),
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            (UINT)(sizeof(EGEG Float4) + sizeof(EGEG Float2)),
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };

    // �T���v���[�X�e�[�g
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

    // �u�����h�X�e�[�g
    constexpr D3D11_RENDER_TARGET_BLEND_DESC kRenderTargetBlendDesc =
    {
        true,                           // BlendEnable
        D3D11_BLEND_SRC_ALPHA,          // SrcBlend
        D3D11_BLEND_INV_SRC_ALPHA,      // DestBlend
        D3D11_BLEND_OP_ADD,             // BlendOp
        D3D11_BLEND_ONE,                // SrcBlendAlpha
        D3D11_BLEND_ZERO,               // DestBlendAlpha
        D3D11_BLEND_OP_ADD,             // BlendOpAlpha
        D3D11_COLOR_WRITE_ENABLE_ALL    // RenderTargetWriteMask
    };
    constexpr D3D11_BLEND_DESC kBlendDesc =
    {
        false,                  // AlphaToCoverageEnable
        false,                  // IndependentBlendEnable
        kRenderTargetBlendDesc  // RenderTarget
    };

} // !unnamed namespace

BEGIN_EGEG
// RendererD3D11
/*===========================================================================*/
// �R���X�g���N�^
RendererD3D11::RendererD3D11( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain ) :
    p_device_( pDevice ),
    p_immediate_context_( pImmediateContext ),
    p_swap_chain_( pSwapChain )
{
    p_device_->AddRef();
    p_immediate_context_->AddRef();
    p_swap_chain_->AddRef();
}

// �f�X�g���N�^
RendererD3D11::~RendererD3D11()
{
    p_render_target_view_->Release();
    p_swap_chain_->Release();
    p_immediate_context_->Release();
    p_device_->Release();
}

// ������
bool RendererD3D11::initialize()
{
    // �p�C�v���C���Ƀ����_�[�^�[�Q�b�g�r���[��ݒ�
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

    // �p�C�v���C���Ƀr���[�|�[�g��ݒ�
    D3D11_TEXTURE2D_DESC desc;
    backbuffer->GetDesc(&desc);
    view_port_.TopLeftX = view_port_.TopLeftY = 0.0F;
    view_port_.Width = static_cast<float>(desc.Width);
    view_port_.Height = static_cast<float>(desc.Height);
    view_port_.MinDepth = 0.0F;
    view_port_.MaxDepth = 1.0F;
    p_immediate_context_->RSSetViewports(1U, &view_port_);

    // �s�v�ɂȂ����o�b�t�@���J��
    backbuffer->Release();

    return true;
}

// ��ʃN���A
void RendererD3D11::clear( const Vector4D& Color )
{
    float color[] = { Color.x, Color.y, Color.z, Color.w };

    p_immediate_context_->ClearRenderTargetView(
        p_render_target_view_,
        color
    );
}

// ���f���`��
void RendererD3D11::renderModel( const Model& Model )
{
    // ���_�o�b�t�@��`
    const D3D11_BUFFER_DESC kBufferDesc =
    {
        sizeof(VertexData)* Model.mesh.vertices.size(),
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_VERTEX_BUFFER,
        0,
        0,
        0
    };

    // �p�C�v���C���̃X�e�[�g�ݒ�
}
END_EGEG
// EOF
