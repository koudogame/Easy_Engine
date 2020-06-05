///
/// @file   render_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_

#include "component.hpp"
#include "mesh.hpp"
#include "shader.hpp"

BEGIN_EGEG

///
/// @class  RenderComponent
/// @brief  �`��R���|�[�l���g
///
class RenderComponent :
    public Component
{
public :
    RenderComponent( LevelNode* Owner ) :
        Component{ Owner } {}

    ///
    /// @brief  ���b�V���̃Z�b�g
    ///
    /// @param[in] Mesh : ���b�V��
    ///
    void setMesh( const Mesh* Mesh ) noexcept { mesh_ = Mesh; }
    ///
    /// @brief  ���b�V���̎擾
    ///
    /// @return �Z�b�g����Ă��郁�b�V��
    ///
    const Mesh* getMesh() const noexcept { return mesh_; }

    ///
    /// @brief  �V�F�[�_�[�̃Z�b�g
    ///
    /// @param[in] Shader : �V�F�[�_�[
    ///
    void setShader( const IShader* Shader ) noexcept { shader_ = Shader; }
    ///
    /// @brief  �V�F�[�_�[�̎擾
    ///
    /// @return �Z�b�g����Ă���V�F�[�_�[
    ///
    const IShader* getShader() const noexcept { return shader_; }

    ///
    /// @brief  �`���Ԃ̃Z�b�g
    ///
    /// @param[in] State : ���
    ///
    /// @details true  : �`����s��  <br>
    ///          false : �`����s��Ȃ�
    ///
    void setState( bool State ) noexcept { is_render_ = State; }
    ///
    /// @brief  �`���Ԃ̎擾
    ///
    /// @return true:�`�悷��@false:�`�悵�Ȃ�
    ///
    bool getState() const noexcept { return is_render_; }

// override
    bool initialize() override;
    void finalize() override;

private :
    bool is_render_;
    const Mesh* mesh_;
    const IShader* shader_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
