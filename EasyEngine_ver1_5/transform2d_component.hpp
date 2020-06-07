///
/// @file   transform2d_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_

#include "component.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Transform2DComponent
/// @brief  2D���W�ϊ��R���|�[�l���g
///
/// @details ���W�̓X�N���[�����W�n�ň����܂��B <br>
///          �p�x�͓x���@�ň����܂��B
///
class Transform2DComponent :
    public Component
{
public :
    Transform2DComponent( LevelNode* Owner ) :
        Component{ Owner } {}

    ///
    /// @brief  �����Z�b�g
    ///
    /// @param[in] Pivot : ��
    ///
    /// @details ���͌��_(����)����̑��Έʒu�ł��B <br>
    ///          { 0.0F, 0.0F }�Ŏ��ƌ��_���������Ȃ�܂��B
    ///
    void setPivot( const Vector2D& Pivot ) noexcept { move(); pivot_ = Pivot; }
    ///
    /// @brief  �����擾
    ///
    /// @return ��
    ///
    const Vector2D& getPivot() const noexcept { return pivot_; }

    ///
    /// @brief  ���W���Z�b�g
    ///
    /// @param[in] Position : ���W
    ///
    /// @details �X�N���[�����W�n�̒l���Z�b�g���Ă��������B
    ///
    void setPosition( const Vector2D& Position ) noexcept { move(); position_ = Position; }
    ///
    /// @brief  ���W���擾
    ///
    /// @return ���W
    ///
    const Vector2D& getPosition() const noexcept { return position_; }
    
    ///
    /// @brief  ��]�x���Z�b�g
    ///
    /// @param[in] Rotation : ��]�x
    ///
    /// @details   �x���@�̒l���Z�b�g���Ă��������B
    ///
    void setRotation( const float Rotation ) noexcept { move(); rotation_ = Rotation; }
    ///
    /// @brief  ��]�x���擾
    ///
    /// @return ��]�x
    ///
    float getRotation() const noexcept { return rotation_; }

    ///
    /// @brief  �g�嗦���Z�b�g
    ///
    /// @param[in] Scale : �g�嗦
    ///
    /// @details { 1.0F, 1.0F } �Ŋe���ɓ��{�ƂȂ�܂��B
    ///
    void setScale( const Vector2D& Scale ) noexcept { move(); scale_ = Scale; }
    ///
    /// @brief  �g�嗦���擾
    ///
    /// @return �g�嗦
    ///
    const Vector2D& getScale() const noexcept { return scale_; }

    ///
    /// @brief  ���[�J�����W�ϊ��s����v�Z
    ///
    /// @return ���[�J�����W�ϊ��s��
    ///
    const Matrix4x4& calcLocalTransformMatrix() const;
    ///
    /// @brief  �O���[�o�����W�ϊ��s����v�Z
    ///
    /// @return �O���[�o�����W�ϊ��s��
    ///
    Matrix4x4 calcGlobalTransformMatrix() const;

// override
    bool initialize() override;
    void finalize() override;

private :
    void move() noexcept { is_moved_ = true; }

    Vector2D pivot_;
    Vector2D position_;
    float    rotation_;
    Vector2D scale_;
    mutable bool is_moved_;
    mutable Matrix4x4 transform_cache_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
/// EOF
