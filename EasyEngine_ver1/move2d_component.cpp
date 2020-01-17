// 作成者 : 板場
#include "move2d_component.hpp"
#include "task_manager.hpp"
#include "task_priority.hpp"

BEGIN_EGEG
// Move2DComponent
/*===========================================================================*/
// 初期化処理
bool Move2DComponent::initialize()
{
    // タスクの登録
    task_.setFunction( this, &Move2DComponent::update );
    TaskManager::instance()->registerTask( TaskPriority::kMoveComponent, &task_ );

    return true;
}

// 終了処理
void Move2DComponent::finalize()
{
    // タスクの登録を解除
    TaskManager::instance()->unregisterTask( &task_ );
}

// 更新処理
void Move2DComponent::update( uint64_t Delta )
{
    erapsed_ += Delta;
}

// 変位の返却
Vector2D Move2DComponent::getDisplacement()
{
    uint64_t curr_erapsed = erapsed_;
    erapsed_ = 0U;

    return direction_ * ( speed_ * curr_erapsed );
}

// 移動角度の設定
void Move2DComponent::setAngle( float AngleDEG )
{
    angle_ = AngleDEG;

    float angle_rad = convertToRadians( AngleDEG );
    direction_.x = std::cos( angle_rad );
    direction_.y = -std::sin( angle_rad );
}
END_EGEG
// EOF
