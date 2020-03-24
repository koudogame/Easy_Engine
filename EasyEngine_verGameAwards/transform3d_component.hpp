///
/// @file   transform3d_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#include "component.hpp"
#include "egeg_math.hpp"
#include "actor3d.hpp"
#include "uid.hpp"
BEGIN_EGEG
///
/// @class  Transform3DComponent
/// @brief  ���[���h���W�̊Ǘ��R���|�[�l���g
///
class Transform3DComponent :
    public Component
{
public :
    static constexpr UID<Transform3DComponent> getID() noexcept { return UID<Transform3DComponent>(); }

    Transform3DComponent( Actor3D* Owner ) :
        Component( Owner )
    {}

    ///< ���W�̃Z�b�g
    void setPosition( const Vector3D& Destination ) noexcept { position_ = Destination; }
    ///< ���W�̎擾
    const Vector3D& getPosition() const noexcept { return position_; }

    ///< �g�k���̃Z�b�g
    void setScale( const Vector3D& Scale ) noexcept { scale_ = Scale; }
    ///< �g�k���̎擾
    const Vector3D& getScale() const noexcept { return scale_; }

    ///< ��]�x���̃Z�b�g
    void setRotation( const Vector3D& Rotation ) noexcept { rotation_ = Rotation; }
    ///< ��]�x���̎擾
    const Vector3D& getRotation() const noexcept { return rotation_; }
        
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize() override;
/*-----------------------------------------------------------------*/
private :
    Vector3D position_;
    Vector3D scale_;
    Vector3D rotation_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
