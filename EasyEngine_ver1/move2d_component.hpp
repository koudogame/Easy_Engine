///
/// @file   move2d_component.hpp
/// @author ��
///
/// @brief  2D�ړ��R���|�[�l���g
///
#ifndef INCLUDED_EGEG_MOVE2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_MOVE2D_COMPONENT_HEADER_
#include "component.hpp"
#include "egeg_math.hpp"
#include "job.hpp"
BEGIN_EGEG
class Move2DComponent :
    public IComponent
{
public :
    ///
    /// @brief  �X�V����
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̎��Ԃ̍�
    ///
    void update( uint64_t DeltaTimeMS );

    ///
    /// @brief   �ψʂ̎擾
    /// @details ���̊֐���O��Ăяo����������̕ψʃx�N�g����ԋp���܂��B
    ///
    /// @return  �ψ�
    ///
    Vector2D getDisplacement();

    ///
    /// @brief  �����̐ݒ�
    ///
    /// @param[in] Speed : ����( pix/sec )
    ///
    void setSpeed( float Speed ) { speed_ = Speed * 0.001F; }
    ///
    /// @brief  �����̎擾
    ///
    /// @return ����
    ///
    float getSpeed() const { return speed_; }

    ///
    /// @brief   �ړ������̐ݒ�
    ///
    /// @param[in] AngleDEG : �ړ��p�x( �x���@ )
    ///
    void setAngle( float AngleDEG );
    ///
    /// @brief  �ړ������̎擾
    ///
    /// @return �ړ�����
    ///
    float getAngle() const { return angle_; }


// IComponent
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

private :
    float    speed_ = 0.0F;                 /// ����( pix/ms )
    float    angle_ = 0.0F;                 /// �p�x( getAngle�Ăяo�����A����v�Z����̂�h�� )
    Vector2D direction_ = { 0.0F, 0.0F };   /// �����x�N�g��( ���K���x�N�g�� )
    uint64_t erapsed_ = 0U;                 /// �o�ߎ���( ms )
    Job      job_;                          /// �W���u�o�^�p
};
END_EGEG
#endif /// !INCLUDED_EGEG_MOVE2D_COMPONENT_HEADER_
/// EOF
