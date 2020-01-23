// ì¬Ò : ”Âê
#include "move2d_component.hpp"
#include "job_scheduler.hpp"
#include "job_priority.hpp"

BEGIN_EGEG
// Move2DComponent
/*===========================================================================*/
// ‰Šú‰»ˆ—
bool Move2DComponent::initialize()
{
    // ƒWƒ‡ƒu‚Ì“o˜^
    job_.setFunction( this, &Move2DComponent::update );
    JobScheduler::instance()->registerJob( JobPriority::kMoveComponent, &job_ );

    return true;
}

// I—¹ˆ—
void Move2DComponent::finalize()
{
    // ƒWƒ‡ƒu‚Ì“o˜^‚ğ‰ğœ
    JobScheduler::instance()->unregisterJob( &job_ );
}

// XVˆ—
void Move2DComponent::update( uint64_t Delta )
{
    erapsed_ += Delta;
}

// •ÏˆÊ‚Ì•Ô‹p
Vector2D Move2DComponent::getDisplacement()
{
    uint64_t curr_erapsed = erapsed_;
    erapsed_ = 0U;

    return direction_ * ( speed_ * curr_erapsed );
}

// ˆÚ“®Šp“x‚Ìİ’è
void Move2DComponent::setAngle( float AngleDEG )
{
    angle_ = AngleDEG;

    float angle_rad = convertToRadians( AngleDEG );
    direction_.x = std::cos( angle_rad );
    direction_.y = -std::sin( angle_rad );
}
END_EGEG
// EOF
