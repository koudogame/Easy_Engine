// �쐬�� : ��
#include "move2d_component.hpp"
#include "task_manager.hpp"
#include "task_priority.hpp"

BEGIN_EGEG
// Move2DComponent
/*===========================================================================*/
// ����������
bool Move2DComponent::initialize()
{
    // �^�X�N�̓o�^
    task_.setFunction( this, &Move2DComponent::update );
    TaskManager::instance()->registerTask( TaskPriority::kMoveComponent, &task_ );

    return true;
}

// �I������
void Move2DComponent::finalize()
{
    // �^�X�N�̓o�^������
    TaskManager::instance()->unregisterTask( &task_ );
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
