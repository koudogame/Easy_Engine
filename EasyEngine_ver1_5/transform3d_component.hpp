///
/// @file   transform3d_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_

#include "component3d.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class Transform3DComponent
/// @brief 3D�A�N�^�[�p���W�ϊ��R���|�[�l���g
///
class Transform3DComponent :
    public Component3D
{
public :
    Transform3DComponent( Actor3D* Owner ) :
        Component3D{ Owner }
    {}

    ///
    /// @brief ���W�̃Z�b�g
    ///
    /// @param[in] Position
    ///
    void setPosition( const Vector3D& Position ) noexcept { position_ = Position; }
    ///
    /// @brief ���W�̎擾
    ///
    /// @return ���W
    ///
    const Vector3D& getPosition() const noexcept { return position_; }

    ///
    /// @brief ��]�p�̃Z�b�g
    ///
    /// @param[in] RotationDeg : ��]�p( �e���x���@ )
    ///
    void setRotationDeg( const Vector3D& RotationDeg ) noexcept { rotation_deg_ = RotationDeg; }
    ///
    /// @brief ��]�p�̎擾
    ///
    /// @return ��]�p( �e���x���@ )
    ///
    const Vector3D& getRotationDeg() const noexcept { return rotation_deg_; }

    ///
    /// @brief  �g�k���̃Z�b�g
    ///
    /// @param[in] Scale : �g�k��
    ///
    void setScale( const Vector3D& Scale ) noexcept { scale_ = Scale; }
    ///
    /// @brief �g�k���̎擾
    ///
    /// @return �g�k��
    ///
    const Vector3D& getScale() const noexcept { return scale_; }

// override
    bool initialize() override;
    void finalize() override;
private :
    Vector3D position_;
    Vector3D rotation_deg_;
    Vector3D scale_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
