// �쐬�� : ��
#include "move2d_component.hpp"
#include "job_scheduler.hpp"
#include "job_priority.hpp"

BEGIN_EGEG
// Move2DComponent
/*===========================================================================*/
// ����������
bool Move2DComponent::initialize()
{
    // �W���u�̓o�^
    job_.setFunction( this, &Move2DComponent::update );
    JobScheduler::instance()->registerJob( JobPriority::kMoveComponent, &job_ );

    return true;
}

// �I������
void Move2DComponent::finalize()
{
    // �W���u�̓o�^������
    JobScheduler::instance()->unregisterJob( &job_ );
}

// �X�V����
void Move2DComponent::update( uint64_t Delta )
{
    erapsed_ += Delta;
}

// �ψʂ̕ԋp
Vector2D Move2DComponent::getDisplacement()
{
    uint64_t curr_erapsed = erapsed_;
    erapsed_ = 0U;

    return direction_ * ( speed_ * curr_erapsed );
}

// �ړ��p�x�̐ݒ�
void Move2DComponent::setAngle( float AngleDEG )
{
    angle_ = AngleDEG;

    float angle_rad = convertToRadians( AngleDEG );
    direction_.x = std::cos( angle_rad );
    direction_.y = -std::sin( angle_rad );
}
END_EGEG
// EOF
