///
/// @file   rendering_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDERING_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDERING_COMPONENT_HEADER_

#include "component.hpp"
#include "mesh.hpp"
#include "scene.hpp"

BEGIN_EGEG

///
/// @class RenderingComponent
/// @brief �`��R���|�[�l���g
///
class RenderingComponent :
    public Component
{
public :
    RenderingComponent( Actor* Owner ) :
        affiliation_scene_{ nullptr },
        Component{ Owner },
        state_{ true }
    {}

    ///
    /// @brief ���b�V���̃Z�b�g
    ///
    /// @param[in] Mesh : ���b�V��
    ///
    /// @details ������Mesh�͕ێ�����V�F�[�_�[�̏��L�҂��ڂ����߁A�E�Ӓl�Q�Ƃœn���Ă��������B
    ///
    void setMesh( const Mesh& Mesh ) noexcept { mesh_ = &Mesh; }
    /// @brief  ���b�V���̎擾
    ///
    /// @return ���b�V��
    ///
    const Mesh& getMesh() const noexcept { return *mesh_; }

    ///
    /// @brief     �`���Ԃ̃Z�b�g
    ///
    /// @param[in] State : �Z�b�g������
    ///
    /// @details   true:�`�悷��@false:�`�悵�Ȃ�
    ///
    void setState( bool State ) noexcept { state_ = State; }
    ///
    /// @brief �`���Ԃ̎擾
    ///
    /// @return true:�`�悷��@false:�`�悵�Ȃ�
    ///
    bool getState() const noexcept { return state_; }

// override
    bool initialize() override;
    void finalize() override;
private :
    Scene* affiliation_scene_;
    bool state_;
    const Mesh* mesh_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_COMPONENT_HEADER_
/// EOF
