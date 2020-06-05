// �쐬�� : ��
/******************************************************************************

    include

******************************************************************************/
#include "move3d_component.hpp"
#include "transform3d_component.hpp"
#include "engine.hpp"
#include "task_order.hpp"
#include "raw_number.hpp"


BEGIN_EGEG

/******************************************************************************

    Move3DComponent

******************************************************************************/
 // ������
bool Move3DComponent::initialize()
{
    last_moved_ = Vector3D{0.0F, 0.0F, 0.0F};
    animation_func_ = nullptr;
    animation_type_ = AnimationControl::kUnspecified;
    is_speed_animated_ = false;
    start_point_ = Vector3D{0.0F, 0.0F, 0.0F};
    direction_ = Vector3D{0.0F, 0.0F, 0.0F};
    start_speed_ = 0.0F;
    displacement_speed_ = 0.0F;
    r_time_required_ = 0.0F;
    time_elapsed_ = 0;
    is_back_ = false;

    task_.setJob( this, &Move3DComponent::update );

    return true;
}


 // �I��
void Move3DComponent::finalize()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_ );
}


 // �X�V
void Move3DComponent::update( uint64_t Delta )
{
    auto* transform = getOwner()->getComponent<Transform3DComponent>();
    if( !transform ) return;

    // �ψʁA�����x�N�g���̌W�����v�Z
    const float kDisplacement = is_speed_animated_ ?
        (start_speed_ + displacement_speed_*animation_func_(calcCurrentTime(Delta)))*Delta
        : start_speed_ * animation_func_(calcCurrentTime(Delta));

    // �ړ��O�̍��W��ێ��������̂ŁA�Q�Ƃł͂Ȃ�
    const Vector3D kLastPosition = transform->getPosition();
    if( animation_type_ == AnimationControl::kNoStop )
        start_point_ = kLastPosition;

    transform->setPosition( start_point_ + direction_*kDisplacement );
    last_moved_ = transform->getPosition() - kLastPosition;
}


 // �ړ�( �������� )
 // �A�j���[�V�����͕K�� easing::linear �ɂȂ�
 // �A�j���[�V�����͂��Ȃ��̂ŁA�t���O�͐ݒ肵�Ȃ��B
void Move3DComponent::move( float Speed, const Vector3D& Direction )
{
    animation_func_ = easing::linear;
    animation_type_ = AnimationControl::kUnspecified;
    is_speed_animated_ = true;
    start_point_ = getOwner()->getComponent<Transform3DComponent>()->getPosition();
    direction_ = Direction;
    start_speed_ = Speed;
    displacement_speed_ = 0.0F;
    r_time_required_ = 1.0F;
    time_elapsed_ = 0;
    is_back_ = false;
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kMove );
}


 // �ړ�( ���x���ω� )
void Move3DComponent::move(
    float Start, 
    float End, 
    uint64_t Time, 
    const Vector3D& Direction, 
    const AnimationFunction& Animation,
    AnimationControl Type )
{
    animation_func_ = Animation;
    animation_type_ = Type;
    is_speed_animated_ = true;
    start_point_ = getOwner()->getComponent<Transform3DComponent>()->getPosition();
    direction_ = Direction;
    start_speed_ = Start;
    displacement_speed_ = End - Start;
    time_required_ = Time;
    r_time_required_ = 1.0F/Time;
    time_elapsed_ = 0;
    is_back_ = false;
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kMove );
}


 // �ړ�( �ʒu���ω� )
void Move3DComponent::move(
    const Vector3D& Start,
    const Vector3D& End,
    uint64_t Time,
    const AnimationFunction& Animation,
    AnimationControl Type
)
{
    animation_func_ = Animation;
    animation_type_ = Type;
    start_point_ = Start;
    direction_ = (End-Start);
    start_speed_ = 0.0F;
    displacement_speed_ = 1.0F;
    time_required_ = Time;
    r_time_required_ = 1.0F/Time;
    time_elapsed_ = 0;
    is_back_ = false;
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kMove );
}


 // �X�g�b�v
void Move3DComponent::stop()
{
    auto* transform = getOwner()->getComponent<Transform3DComponent>();
    if( !transform ) return;

    start_point_ = transform->getPosition();
    start_speed_ = 0.0F;
    displacement_speed_ = 0.0F;
}


 // ���ݎ��Ԃ̎擾
float Move3DComponent::calcCurrentTime( uint64_t Delta )
{
    time_elapsed_ += is_back_ ? -static_cast<int64_t>(Delta) : Delta;
    float time = time_elapsed_*r_time_required_;

    if( time > 1.0F )
    {
        switch( animation_type_ )
        {
        case AnimationControl::kUnspecified :
            EasyEngine::getTaskManager()->unregisterJob( &task_ );
            break;

        case AnimationControl::kNoStop :
            time_elapsed_=time_required_; // �I�[�o�[�t���[�h�~
            start_point_ = getOwner()->getComponent<Transform3DComponent>()->getPosition();
            time = 1.0F;
            break;

        case AnimationControl::kOnce :
            time = 1.0F;
            EasyEngine::getTaskManager()->unregisterJob( &task_ );
            break;

        case AnimationControl::kLoop :
            // ���߂������i�񂾂Ƃ�����J�n�ʒu�Ƃ���
            time_elapsed_%=time_required_;
            time = time_elapsed_*r_time_required_;
            break;

        case AnimationControl::kBack :
        case AnimationControl::kLoopBack :
            // 1 - ���߂������A�����݂̎��ԂƂ���
            is_back_ = true;
            time_elapsed_ = time_required_ - (time_elapsed_-time_required_);
            time = time_elapsed_*r_time_required_;
            break;
        }
    }
    else if( time < 0.0F )
    {
        switch( animation_type_ )
        {
        case AnimationControl::kBack :
            time = 0.0F;
            EasyEngine::getTaskManager()->unregisterJob( &task_ );

            break;

        case AnimationControl::kLoopBack :
            // 0 - ���߂������A�����݂̎��ԂƂ���
            is_back_ = false;
            time_elapsed_ *= -1;
            time = time_elapsed_*r_time_required_;

            break;

        default :
            time =  0.0F;
        }
        
    }

    return time;
}

END_EGEG
// EOF
