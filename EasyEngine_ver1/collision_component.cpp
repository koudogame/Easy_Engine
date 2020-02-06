// 作成者 : 板場
#include "collision_component.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionComponent : 関数の実装
/*===========================================================================*/
// 衝突の検出
void CollisionComponent::notifyCollision( Actor* pOther )
{
    // 衝突を検出したら、衝突後の処理を呼び出す
    if( owner_->getShape()->isCollided(pOther->getShape()) )
    {
        auto function = post_collision_.find( pOther->getID() );
        if( function != post_collision_.end() )
        {
            function->second( pOther );
        }
    }
}
END_EGEG
// EOF
