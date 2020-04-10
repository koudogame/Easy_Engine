///
/// @file   scene3d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE3D_HEADER_
#define INCLUDED_EGEG_SCENE3D_HEADER_

#include <array>
#include <set>
#include "scene.hpp"
#include "camera3d.hpp"
#include "actor3d.hpp"

BEGIN_EGEG

///
/// @class   Scene3D
/// @brief   3D�V�[��
/// @details prepare�֐��ł́A�z�u����Ă��郂�f�����N���A���܂��B                                               <br>
///          ���f���̃G���g���[�́Aprepare�Ăяo������Arender�Ăяo���̊Ԃɍs���ĉ������B                       <br>
///          ����̃V�[���𕡐���`�悵�����ꍇ���́A                                                            <br>
///          ��x��prepare�֐��Ăяo���ɑ΂��ĕ�����render�֐����Ăяo���ĉ������B                               <br>
///          ���[�v���ׂ��ł�render�֐��Ăяo�����\�ł����A�\�����ʕs��������\��������̂Ŕ����Ă��������B<br>
///          ���̃V�[�����V�F�[�_�[�ɃZ�b�g����萔�o�b�t�@�́A                                                  <br>
///          �u���_�V�F�[�_�\�v                                                                                  <br>
///             b0 : �ˉe�ϊ��s��
///             b1 : �r���[�ϊ��s��
///             b2 : ���[���h�ϊ��s��                                                                            <br>
///          �ł��B
///
class Scene3D :
    public Scene
{
public :
    ///
    /// @brief  �J�����̃Z�b�g
    ///
    /// @param[in] Camera : �J����
    ///
    void setCamera( const Camera3D* Camera ) noexcept { camera_ = Camera; }

    ///
    /// @brief  �A�N�^�[�̃G���g���[
    ///
    /// @param[in] Actor : �`�悷��A�N�^�[
    ///
    void entry( const Actor3D* Actor ) { actor_list_.emplace( Actor ); }
    ///
    /// @brief   �A�N�^�[�̃G���g���[����
    ///
    /// @param[in] Actor : �G���g���[����������A�N�^�[
    ///
    void exit( const Actor3D* Actor ) { actor_list_.erase( Actor ); }
    
    
/*-----------------------------------------------------------------*/
// Scene
    bool initialize( RenderingManager* ) override;
    void finalize() override;
    void prepare() override;
    void render( 
        ID3D11DeviceContext*,
        const std::vector<ID3D11RenderTargetView*>&,
        const std::vector<D3D11_VIEWPORT>&,
        const std::vector<D3D11_RECT>&,
        ID3D11DepthStencilView* = nullptr,
        ID3D11DepthStencilState* = nullptr,
        UINT = 0,
        ID3D11RasterizerState* = nullptr,
        ID3D11BlendState* = nullptr,
        float* = nullptr,
        UINT = 0xFFFFFFFF ) override;
/*-----------------------------------------------------------------*/

private :
    const Camera3D* camera_ = nullptr;
    std::set<const Actor3D*> actor_list_;

    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U> cbuffers_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SCENE3D_HEADER_
/// EOF
