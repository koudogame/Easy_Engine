///
/// @file   scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_

#include <array>
#include <vector>
#include <unordered_set>
#include <wrl.h>
#include <d3d11.h>
#include "non_copyable.hpp"

BEGIN_EGEG

class RenderingComponent; ///< RenderingComponent�O���錾( �z�Q�Ɖ�� )

///
/// @class Scene
/// @brief �V�[��( �����_�����O�P�� )
///
class Scene :
    NonCopyable<Scene>
{
public :
    ///
    /// @brief ������
    ///
    /// @param[in] Device : D3D�f�o�C�X
    ///
    /// @return true:�����@false:���s
    ///
    bool initialize( ID3D11Device* Device );

    ///
    /// @brief �I��
    ///
    void finalize();

    ///
    /// @brief �J�������Z�b�g
    ///
    /// @param[in] Camera : �J����
    ///
    void setCamera( const void* Camera ) noexcept { /*camera_ = Camera;*/ }

    ///
    /// @brief �V�[���X�e�[�g�̐ݒ�
    ///
    /// @param[in] RenderTargetViews : �`��^�[�Q�b�g���X�g
    /// @param[in] Viewports         : �r���[�|�[�g���X�g
    /// @param[in] ScissorRects      : �V�U�[��`���X�g
    /// @param[in] DepthStencilView  : �[�x�X�e���V���r���[
    /// @param[in] DepthStencilState : �[�x�X�e���V���X�e�[�g
    /// @param[in] StencilReference  : �X�e���V���e�X�g�p�Q�ƒl
    /// @param[in] RasterizerState   : ���X�^���C�U�X�e�[�g
    /// @param[in] BlendState        : �u�����h�X�e�[�g
    /// @param[in] BlendFactor       : D3D11_BLEND_BLEND_FACTOR�g�p���Ɏg�p����萔�l
    /// @param[in] BlendMask         : �}���`�T���v���p�}�X�N
    ///
    /// @details �R���e�i���g�p���������ɂ��āA�����悭�������ߒl�n���ɂȂ��Ă��܂��B<br>
    ///           ���b���󂯂邽�߂ɂ͂ɂ�std::move(...)���g�p���ĉ�����
    ///
    void setState(
        std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> RenderTargetViews,
        std::vector<D3D11_VIEWPORT> Viewports,
        std::vector<D3D11_RECT> ScissorRects,
        const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& DepthStencilView = {},
        const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& DepthStencilState = {},
        UINT StencilReference = 0,
        const Microsoft::WRL::ComPtr<ID3D11RasterizerState>& RasterizerState = {},
        const Microsoft::WRL::ComPtr<ID3D11BlendState>& BlendState = {},
        const std::array<float, 4>& BlendFactor = { 0.0F, 0.0F, 0.0F, 0.0F},
        UINT BlendMask = 0xFFFFFFFF ) noexcept;

    ///
    /// @brief  �V�[���̃N���A
    ///
    /// @param[in] DC    : �f�o�C�X�R���e�L�X�g
    /// @param[in] Color : �N���A�F
    ///
    void clear( ID3D11DeviceContext* DC, const std::array<float, 4>& Color = {1.0F, 1.0F, 1.0F, 1.0F} );
    ///
    /// @brief �V�[���̕`��
    ///
    /// @param[in] DC : �f�o�C�X�R���e�L�X�g
    ///
    void render( ID3D11DeviceContext* DC );

    ///
    /// @brief �`��I�u�W�F�N�g��ǉ�
    ///
    /// @param[in] Component : �ǉ��Ώ�
    ///
    void entry( const RenderingComponent* Component ) { models_.emplace( Component ); }
    ///
    /// @brief �`��I�u�W�F�N�g���폜
    ///
    /// @param[in] Component : �폜�Ώ�
    ///
    void exit( const RenderingComponent* Component ) noexcept { models_.erase( Component ); }

private :
    std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> render_target_views_;
    std::vector<D3D11_VIEWPORT> viewports_;
    std::vector<D3D11_RECT>     scissor_rects_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    UINT stencil_reference_ = 0;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    std::array<float, 4U> blend_factor_;
    UINT blend_mask_ = 0;
    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U> cbuffers_;
    const void* camera_ = nullptr;
    std::unordered_set<const RenderingComponent*> models_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
