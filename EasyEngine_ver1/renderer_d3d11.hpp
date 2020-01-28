///
/// @file   renderer_d3d11.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDERER_D3D11_HEADER_
#define INCLUDED_EGEG_RENDERER_D3D11_HEADER_
#include <deque>
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EGEG
///
/// @class  RendererD3D11
///
/// @brief  DirectX11�p�����_���[
///
class RendererD3D11 :
    public IRenderer
{
public :
    ///
    /// @brief   �R���X�g���N�^
    ///
    /// @param[in] pDevice : D3D�f�o�C�X
    /// @param[in] pImmediateContext : D3D�f�o�C�X�R���e�L�X�g
    /// @param[in] pSwapChain : DXGI�X���b�v�`�F�C��
    ///
    RendererD3D11( ID3D11Device* pDevice, 
                   ID3D11DeviceContext* pImmediateContext,
                   IDXGISwapChain* pSwapChain );
    ///
    /// @brief   ������
    /// @details ������ɕK���Ăяo���Ă��������B
    ///
    /// @return  ����������[ true ] ���������s[ false ]
    ///
    bool initialize();

// IRenderer
/*-----------------------------------------------------------------*/
    Vector2D getScreenSize() const override { return {viewport_.Width, viewport_.Height}; }
    void clear( const Vector4D& ) override;
    void beginRender() override;
    void renderModel( const Model&, BlendMode ) override;
    void endRender() override;

private :
    ~RendererD3D11();

    ID3D11Device*           p_device_;              /// D3D11�f�o�C�X
    ID3D11DeviceContext*    p_immediate_context_;   /// D3D11�f�o�C�X�R���e�L�X�g
    IDXGISwapChain*         p_swap_chain_;          /// DXGI�X���b�v�`�F�C��
    ID3D11RenderTargetView* p_render_target_view_;  /// D3D11�����_�[�^�[�Q�b�g�r���[
    D3D_FEATURE_LEVEL       feature_level_;         /// �̗p���ꂽ�@�\���x��
    D3D11_VIEWPORT          viewport_;              /// �r���[�|�[�g
    ID3D11SamplerState*     p_sampler_state_;       /// �T���v���[�X�e�[�g
    ID3D11BlendState*       p_blend_states_[3];     /// �u�����h�X�e�[�g�z��
    std::deque<Model>       model_list_;            /// �`��o�b�`
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_D3D11_HEADER_
/// EOF
