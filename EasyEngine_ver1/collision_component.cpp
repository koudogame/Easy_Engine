// �쐬�� : ��
#include "collision_component.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionComponent : �֐��̎���
/*===========================================================================*/
// �Փ˂̌��o
void CollisionComponent::notifyCollision( Actor* pOther )
{
    // �Փ˂����o������A�Փˌ�̏������Ăяo��
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
