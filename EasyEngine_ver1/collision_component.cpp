// �쐬�� : ��
#include "collision_component.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionComponent : �֐��̎���
/*===========================================================================*/
// �Փ˂̌��o
void CollisionComponent::notifyCollision( const CollisionComponent* pOther )
{
    // �Փ˂����o������A�Փˌ�̏������Ăяo��
    if( owner_->getShape()->isCollided(pOther->owner_->getShape()) )
    {
        auto function = post_collision_.find( pOther->owner_->getID() );
        if( function != post_collision_.end() )
        {
            function->second( pOther->owner_ );
        }
    }
}
END_EGEG
// EOF
