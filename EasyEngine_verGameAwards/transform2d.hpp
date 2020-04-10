///
/// @file   transform2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_

#include "component2d.hpp"
#include "egeg_math.hpp"
#include "type_id.hpp"

BEGIN_EGEG
namespace component
{

class Transform2D :
    public Component2D
{
public :
    static constexpr TypeID<Transform2D> getID() noexcept { return TypeID<Transform2D>(); }
    
    Transform2D( Actor2D* Owner ) :
        Component2D( Owner )
    {
    }

    ///< ���W�̃Z�b�g
    void setPosition( const Vector2D& Destination ) noexcept { position_ = Destination; }
    ///< ���W�̎擾
    const Vector2D& getPosition() const noexcept { return position_; }

    ///
    /// @brief  ���̃Z�b�g
    /// @detais �摜���ォ��̑��Έʒu�Ŏw�肵�ĉ������B
    ///         �l��(0,0)���� ~ (1,1)�E�� �͈̔͂Ŏw�肵�ĉ������B
    void setPivot( const Vector2D& Pivot ) noexcept { pivot_ = Pivot; }
    ///< ���̎擾
    const Vector2D& getPivot() const noexcept { return pivot_; }

    ///< �g�k���̐ݒ�
    void setScale( const Vector2D& Scale ) noexcept { scale_ = Scale; }
    ///< �g�k���̎擾
    const Vector2D& getScale() const noexcept { return scale_; }

    ///< ��]�x���̃Z�b�g
    void setRotation( float Rotation ) noexcept { rotation_ = Rotation; }
    ///< ��]�x���̎擾
    float getRotation() const noexcept { return rotation_; }

/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize() override;
/*-----------------------------------------------------------------*/
private :
    Vector2D position_; ///< ����
    Vector2D pivot_;    ///< ��
    Vector2D scale_;
    float rotation_;
};

} // namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM2D_HEADER_
/// EOF
