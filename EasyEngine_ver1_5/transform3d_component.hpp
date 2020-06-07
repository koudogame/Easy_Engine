///
/// @file   transform3d_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_

#include "component.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Transform3DComponent
/// @brief  3D���W�ϊ��R���|�[�l���g
///
/// @details 3D���W�n�ň����܂��B <br>
///          ��]�p�͓x���@�ň����܂��B
///
class Transform3DComponent :
    public Component
{
public :
    Transform3DComponent( LevelNode* Owner ) :
        Component{ Owner } {}

    ///
    /// @brief  ���W���Z�b�g
    ///
    /// @param[in] Position : ���W
    ///
    void setPosition( const Vector3D& Position ) noexcept { move(); position_ = Position; }
    ///
    /// @brief  ���W���擾
    ///
    /// @return ���W
    ///
    const Vector3D& getPosition() const noexcept { return position_; }

    ///
    /// @brief  �e���̉�]�p��ݒ�
    ///
    /// @param[in] Rotation : �e���̉�]�p
    ///
    ///
    void setRotation( const Vector3D& Rotation ) noexcept { move(); rotation_ = Rotation; }
    ///
    /// @brief  �e���̉�]�p���擾
    ///
    /// @return �e���̉�]�p
    ///
    const Vector3D& getRotation() const noexcept { return rotation_; }

    ///
    /// @brief  �g�嗦��ݒ�
    ///
    /// @param[in] Scale : �g�嗦
    ///
    /// @details { 1.0F, 1.0F, 1.0F } �Ŋe���ɓ��{�ƂȂ�܂��B
    ///
    void setScale( const Vector3D& Scale ) noexcept { move(); scale_ = Scale; }
    ///
    /// @brief  �g�嗦���擾
    ///
    /// @return �g�嗦
    ///
    const Vector3D& getScale() const noexcept { return scale_; }

    ///
    /// @brief  ���[�J���ϊ����W���v�Z
    ///
    /// @return ���[�J�����W�s��
    ///
    const Matrix4x4& calcLocalTransformMatrix() const;
    ///
    /// @brief  ���[���h�ϊ��s����v�Z
    ///
    /// @return ���[���h�ϊ��s��
    ///
    Matrix4x4 calcGlobalTransformMatrix() const;

// override
    bool initialize() override;
    void finalize() override;

private :
    void move() noexcept { is_moved_ = true; }

    Vector3D position_;
    Vector3D rotation_;
    Vector3D scale_;
    mutable bool is_moved_;
    mutable Matrix4x4 transform_cache_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
