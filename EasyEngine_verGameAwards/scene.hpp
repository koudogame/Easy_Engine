///
/// @file   scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include "egeg_utility.hpp"
#include "rendering_engine.hpp"
BEGIN_EGEG
///
/// @class   Scene
/// @brief   �����_�����O�P��
/// @details �h���N���X�̓V�[���ւ̃��f���̓o�^�֐����e����`���ĉ������B
///
class Scene :
    NonCopyable<Scene>
{
public :
    Scene( ID3D11DeviceContext* DeviceContext ) :
        device_context_( DeviceContext )
    {
        device_context_->AddRef();
    }
    virtual ~Scene() { device_context_->Release(); }

    virtual void render() = 0;

protected :
    ID3D11DeviceContext* device_context_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
