///
/// @file   scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_

#include <type_traits>
#include <wrl.h>
#include <d3d11.h>
#include "noncopyable.hpp"
#include "easy_engine.hpp"

BEGIN_EGEG

///
/// @class   Scene
/// @brief   �����_�����O�P��
///
class Scene :
    NonCopyable<Scene>
{
public :
    virtual ~Scene() = default;

    ///< ����������
    virtual bool initialize( RenderingManager* Manager ) = 0;

    ///< �I������
    virtual void finalize() = 0;

    ///
    /// @brief  �`�揀��
    ///
    virtual void prepare() = 0;

    ///
    /// @brief  �`��
    ///
    /// @param[in] ImmediateContext  : �f�o�C�X�R���e�L�X�g
    /// @param[in] RenderTargetView  : �`��^�[�Q�b�g�r���[
    /// @param[in] Viewports         : �r���[�|�[�g
    /// @param[in] ScissorRects:     : �V�U�[��`
    /// @param[in] DepthStencilView  : �[�x�X�e���V���r���[
    /// @param[in] DepthStencilState : �[�x�X�e���V���X�e�[�g
    /// @param[in] StencilRef        : �X�e���V���e�X�g�Ŏg�p����Q�ƒl
    /// @param[in] RasterizerState   : ���X�^���C�U�X�e�[�g
    /// @param[in] BlendState        : �u�����h�X�e�[�g
    /// @param[in] BlendFactor       : �u�����h�X�e�[�g�萔
    /// @param[in] BlendMask         : �u�����h�X�e�[�g�T���v���p�}�X�N
    ///
    virtual void render(
        ID3D11DeviceContext* DeviceContext,
        const std::vector<ID3D11RenderTargetView*>& RenderTargetViews,
        const std::vector<D3D11_VIEWPORT>& Viewports,
        const std::vector<D3D11_RECT>& ScissorRects,
        ID3D11DepthStencilView* DepthStencilView = nullptr,
        ID3D11DepthStencilState* DepthStencilState = nullptr,
        UINT StencilRef = 0,
        ID3D11RasterizerState* RasterizerState = nullptr,
        ID3D11BlendState* BlendState = nullptr,
        float* BlendFactor = nullptr,
        UINT BlendMask = 0xFFFFFFFF ) = 0;

protected :
    void setSceneState(
        ID3D11DeviceContext*,
        const std::vector<ID3D11RenderTargetView*>&,
        const std::vector<D3D11_VIEWPORT>&,
        const std::vector<D3D11_RECT>&,
        ID3D11DepthStencilView*,
        ID3D11DepthStencilState*,
        UINT,
        ID3D11RasterizerState*,
        ID3D11BlendState*,
        float*,
        UINT );
};

END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
