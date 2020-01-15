///
/// @file   renderer_windows.hpp
/// @author ��
///
/// @brief  Windows�p�����_���[
///
#ifndef INCLUDED_EGEG_RENDERER_WINDOWS_HEADER_
#define INCLUDED_EGEG_RENDERER_WINDOWS_HEADER_
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EGEG
class RendererWindows :
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
    RendererWindows( ID3D11Device* pDevice, 
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
    void beginRender( const Vector4D& ) override;
    void entryRender( const Model& ) override;
    void endRender() override;

private :
    ~RendererWindows();

    ID3D11Device*           p_device_;              /// D3D11�f�o�C�X
    ID3D11DeviceContext*    p_immediate_context_;   /// D3D11�f�o�C�X�R���e�L�X�g
    IDXGISwapChain*         p_swap_chain_;          /// DXGI�X���b�v�`�F�C��
    ID3D11RenderTargetView* p_render_target_view_;  /// D3D11�����_�[�^�[�Q�b�g�r���[
    D3D_FEATURE_LEVEL       feature_level_;         /// �̗p���ꂽ�@�\���x��
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_WINDOWS_HEADER_
/// EOF