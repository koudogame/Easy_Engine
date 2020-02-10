// 作成者 : 板場
#include "collision_component.hpp"
#include "collision_space.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionComponent : 関数の実装
/*===========================================================================*/
// 衝突の検出
void CollisionComponent::notifyCollision( const CollisionComponent* pOther )
{
    // 衝突を検出したら、衝突後の処理を呼び出す
    if( owner_->getShape()->isCollided(pOther->owner_->getShape()) )
    {
        auto function = post_collision_.find( pOther->owner_->getID() );
        if( function != post_collision_.end() )
        {
            function->second( pOther->owner_ );
        }
    }
}

// 初期化
bool CollisionComponent::initialize()
{
    CollisionSpace::instance()->entry( this );
    return true;
}
// 終了
void CollisionComponent::finalize()
{
    CollisionSpace::instance()->exit( this );
}
END_EGEG
// EOF
