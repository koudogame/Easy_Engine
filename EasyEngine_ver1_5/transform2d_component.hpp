///
/// @file   transform2d_component.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_

#include "component2d.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class Transform2DComponent
/// @brief 2D�A�N�^�[�p���W�ϊ��R���|�[�l���g
///
class Transform2DComponent :
    public Component2D
{
public :
    Transform2DComponent( Actor2D* Owner ) :
        Component2D{ Owner }
    {}

    ///
    /// @brief  ���S�̃Z�b�g
    ///
    /// @param[in] Pivot : ���S
    ///
    /// @details ���W( Position )����̑��΍��W
    ///
    void setPivot( const Vector2D& Pivot ) noexcept { pivot_ = Pivot; }
    ///
    /// @brief  ���S�̎擾
    ///
    /// @return ���S
    ///
    const Vector2D& getPivot() const noexcept { return pivot_; }

    ///
    /// @brief ���W�̃Z�b�g
    ///
    /// @param[in] Position : ���W
    ///
    /// @details ���オ��_
    ///
    void setPosition( const Vector2D& Position ) noexcept { position_ = Position; }
    ///
    /// @brief ���W�̎擾
    ///
    /// @return ���W
    ///
    const Vector2D& getPosition() const noexcept { return position_; }

    ///
    /// @brief ��]�p�x�̃Z�b�g
    ///
    /// @param[in] RotationDeg : ��]�p( �x���@ )
    ///
    void setRotationDeg( float RotationDeg ) noexcept { rotation_angle_deg_ = RotationDeg; }
    ///
    /// @brief ��]�p�x�̎擾
    ///
    /// @return ��]�p�x( �x���@ )
    ///
    float getRotationDeg() const noexcept { return rotation_angle_deg_; }

    ///
    /// @brief �g�k���̃Z�b�g
    ///
    /// @param[in] Scale : �g�k��
    ///
    void setScale( const Vector2D& Scale ) noexcept { scale_ = Scale; }
    ///
    /// @brief �g�k���̎擾
    ///
    /// @return �g�k��
    ///
    const Vector2D& getScale() const noexcept { return scale_; }

// override
    bool initialize() override;
    void finalize() override;
private :
    Vector2D pivot_;
    Vector2D position_;
    float rotation_angle_deg_;
    Vector2D scale_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
/// EOF
