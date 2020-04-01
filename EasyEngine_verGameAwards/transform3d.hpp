///
/// @file   transform3d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#include "component3d.hpp"
#include "egeg_math.hpp"
#include "uid.hpp"

BEGIN_EGEG
namespace component {

///
/// @class  Transform3D
/// @brief  ���[���h���W�̊Ǘ��R���|�[�l���g
///
class Transform3D :
    public Component3D
{
public :
    static constexpr UID<Transform3D> getID() noexcept { return UID<Transform3D>(); }

    Transform3D( Actor3D* Owner ) :
        Component3D( Owner )
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

} /// namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
