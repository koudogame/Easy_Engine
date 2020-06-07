///
/// @file   default_base_scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_DEFAULT_BASE_SCENE_HEADER_
#define INCLUDED_EGEG_DEFAULT_BASE_SCENE_HEADER_

#include <array>
#include <vector>
#include <wrl.h>
#include <d3d11.h>
#include "level_scene.hpp"
#include "task.hpp"

BEGIN_EGEG

///
/// @class   DefaultBaseScene
/// @brief   �f�t�H���g�x�[�X�V�[��
///
/// @details �f�t�H���g�̃x�[�X�V�[���ł��B �E�B���h�E�ɏ������݂��s���܂��B   <br>
///          ���� <br>
///           ���̃N���X�Ɍ��炸�A�x�[�X�V�[���̓��x���t�@�C���ɂ����āA���̃V�[��������ɒ�`����K�v������܂��B <br>
///           initialize�ɓn���p�����[�^�͂���܂���B  <br>
///          ����                                   <br>
///           �V�F�[�_�[�ɓn���萔�o�b�t�@�ɂ���    <br>
///            ���_�V�F�[�_�[ b0 : �ˉe�ϊ��s��      <br>
///            ���_�V�F�[�_�[ b1 : �r���[�ϊ��s��     <br>
///            ���_�V�F�[�_�[ b2 : ���[���h�ϊ��s�� �ȏ�ł��B
///           
class DefaultBaseScene :
    public LevelScene
{
public :
// override
    bool initialize( std::istream& ) override;
    void finalize() override;
    void entry( RenderComponent* ) override;
    void exit( RenderComponent* ) override;
    void setCamera( LevelCamera* Camera ) override { camera_ = Camera; }
    void addLight( LevelLight* ) override;
    void render( uint64_t ) override;

private :
    bool initializeSceneState();
    void bulidPipeline( ID3D11DeviceContext* );
    bool updateViewMatrix( ID3D11DeviceContext* ) const;
    bool updateWorldMatrix( ID3D11DeviceContext*, LevelNode* ) const;

    Task task_;
    LevelCamera* camera_ = nullptr;
    std::vector<RenderComponent*> models_;
    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3> cbuffers_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_DEFAULT_BASE_SCENE_HEADER_
/// EOF
