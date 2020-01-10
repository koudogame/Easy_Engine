///
/// @file   renderer_d3d11.hpp
/// @author ��
///
/// @brief  Direct3D11���g�p���������_���[�ł��B<br>
///         RendererFactory�ɂ�萶������܂��B
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
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pDevice : D3D�f�o�C�X
    /// @param[in] pImmediateContext : D3D�f�o�C�X�R���e�L�X�g
    /// @param[in] pSwapChain : DXGX�X���b�v�`�F�C��
    ///
    RendererD3D11( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain ) :
        p_device_( pDevice ),
        p_immediate_context_( pImmediateContext ),
        p_swap_chain_( pSwapChain )
    {
        p_device_->AddRef();
        p_immediate_context_->AddRef();
        p_swap_chain_->AddRef();
    }
    ///
    /// @brief  ����������
    ///
    /// @return �������ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool initialize();

// IRenderer
/*-----------------------------------------------------------------*/
    void beginRender( float* ) override;
    void setVertexShader( IVertexShader* ) override;
    void setPixelShader( IPixelShader* ) override;
    void setTexture( ITexture* ) override;
    void render( const Mesh& ) override;
    void endRender() override;

private :
    ~RendererD3D11();

    ID3D11Device*           p_device_ = nullptr;                /// D3D�f�o�C�X�C���^�[�t�F�C�X
    ID3D11DeviceContext*    p_immediate_context_ = nullptr;     /// D3D�f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
    IDXGISwapChain*         p_swap_chain_ = nullptr;            /// DXGI�X���b�v�`�F�C���C���^�[�t�F�X
    ID3D11RenderTargetView* p_render_target_view_ = nullptr;    /// D3D�`��^�[�Q�b�g�r���[�C���^�[�t�F�C�X
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
/// EOF
