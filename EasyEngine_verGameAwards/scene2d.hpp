///
/// @file   scene2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE2D_HEADER_
#define INCLUDED_EGEG_SCENE2D_HEADER_

#include <array>
#include <set>
#include "scene.hpp"
#include "camera2d.hpp"
#include "actor2d.hpp"
#include "vertex.hpp"

BEGIN_EGEG

///
/// @class   Scene2D
/// @brief   2D�V�[��
/// @details prepare�֐��ł́A�z�u����Ă��郂�f�����N���A���܂��B                                                <br>
///          �A�N�^�[�̃G���g���[�́Aprepare�Ăяo������render�Ăяo���̊Ԃɍs���ĉ������B                        <br>
///          ����̃V�[���𕡐���`�悵�����ꍇ���́A                                                             <br>
///          ��x��prepare�֐��Ăяo���ɑ΂��ĕ�����render�֐����Ăяo���ĉ������B                                <br>
///          ���[�v���ׂ��ł�render�֐��Ăяo�����\�ł����A�\�����ʕs��������\��������̂Ŕ����Ă��������B <br>
///          ���̃V�[�����V�F�[�_�[�ɃZ�b�g����萔�o�b�t�@�o�b�t�@�́A                                                       <br>
///          �u���_�V�F�[�_�\�v                                                                                   <br>
///             b0 : �r���[�ϊ��s�� 
///             b1 : ���[���h�ϊ��s��                                                                             <br>
///          ���̃V�[�����V�F�[�_�[�ɃZ�b�g����V�F�[�_�\���\�[�X�r���[�́A                                       <br>
///          �u�s�N�Z���V�F�[�_�\�v                                                                               <br>
///             t0 : ���C���e�N�X�`��( �f�B�t���[�Y�e�N�X�`�� )                                                   <br>
///          �ł��B
///
class Scene2D :
    public Scene
{
public :
    ///
    /// @brief  �J�����̃Z�b�g
    ///
    /// @param[in] Camera : 2D��ԗp�J����
    ///
    void setCamera( const Camera2D* Camera ) noexcept { camera_ = Camera; }

    ///
    /// @brief  �A�N�^�[�̃G���g���[
    ///
    /// @param[in] Actor : 2D�A�N�^�[
    ///
    void entry( const Actor2D* Actor ) { actor_list_.emplace( Actor ); }
    ///
    /// @brief  �A�N�^�[�̃G���g���[����
    ///
    /// @param[in] Actor : �G���g���[����������A�N�^�[
    ///
    void exit( const Actor2D* Actor ) { actor_list_.erase( Actor ); }


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
    const Camera2D* camera_ = nullptr;
    std::set<const Actor2D*> actor_list_;
    std::array<ID3D11Buffer*, 2U> cbuffer_list_;
    Vertex vertices_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SCENE2D_HEADER_
/// EOF
