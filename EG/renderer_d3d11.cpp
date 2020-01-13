// �쐬�� : ��
#include "renderer_d3d11.hpp"
#include <fstream>
#include "DirectXTex/DirectXTex.h"
#include "vertex_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"
#include "texture_d3d11.hpp"

#pragma comment( lib, "d3d11.lib" )

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif

BEGIN_EGEG
// �֐��̎���
/*===========================================================================*/
// �`��J�n
void RendererD3D11::beginRender(float* Color )
{
    p_immediate_context_->ClearRenderTargetView( p_render_target_view_, Color );
}
// ���_�V�F�[�_�\�̃Z�b�g
void RendererD3D11::setVertexShader( IVertexShader* pVertexShader )
{
    ID3D11VertexShader* p_d3d11_vs = 
        static_cast<VertexShaderD3D11*>(pVertexShader)->get();

    p_immediate_context_->VSSetShader( p_d3d11_vs, nullptr, 0 ); 
}
// �s�N�Z���V�F�[�_�̃Z�b�g
void RendererD3D11::setPixelShader( IPixelShader* pPixelShader )
{
    ID3D11PixelShader* p_d3d11_ps =
        static_cast<PixelShaderD3D11*>(pPixelShader)->get();

    p_immediate_context_->PSSetShader( p_d3d11_ps, nullptr, 0 );
}
// �e�N�X�`���̃Z�b�g
void RendererD3D11::setTexture( ITexture* pTexture )
{
    ID3D11ShaderResourceView* p_d3d11_srv =
        static_cast<TextureD3D11*>(pTexture)->get();

    p_immediate_context_->PSSetShaderResources( 0, 0, &p_d3d11_srv );
}
// ���f���̕`��
void RendererD3D11::render(const Mesh& Object)
{

}
// �`��I��
void RendererD3D11::endRender()
{
    if( p_swap_chain_->Present(0, DXGI_PRESENT_TEST) == S_OK )
        p_swap_chain_->Present( 0, 0 );
}

// ����������
bool RendererD3D11::initialize()
{
    // �`��^�[�Q�b�g���p�C�v���C���ɐݒ�
    ID3D11Texture2D* buffer;
    if( FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer)) )
        return false;
    if( FAILED(p_device_->CreateRenderTargetView(buffer, nullptr, &p_render_target_view_)) )
    {
        buffer->Release();
        return false;
    }
    p_immediate_context_->OMSetRenderTargets( 1, &p_render_target_view_, nullptr );

    // �r���[�|�[�g���p�C�v���C���ɐݒ�
    D3D11_TEXTURE2D_DESC desc;
    buffer->GetDesc( &desc );
    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<float>(desc.Width);
    vp.Height = static_cast<float>(desc.Height);
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    p_immediate_context_->RSSetViewports( 1, &vp );

    buffer->Release();

    return true;
}

// �f�X�g���N�^
RendererD3D11::~RendererD3D11()
{
    // �t���X�N���[�����[�h������
    p_swap_chain_->SetFullscreenState(false, nullptr);

    // �p�C�v���C���̃X�e�[�g�ݒ���N���A
    p_immediate_context_->ClearState();

    // �e��C���^�[�t�F�C�X�����
    p_render_target_view_->Release();
    p_swap_chain_->Release();
    p_immediate_context_->Release();
    p_device_->Release();
}
END_EGEG
// EOF
