// �쐬�� : ��
#include "collision_component.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionComponent : �֐��̎���
/*===========================================================================*/
// �Փ˂̌��o
bool CollisionComponent::isCollided( const CollisionComponent* pOther )
{
    bool is_collided = owner_->getShape()->isCollided( pOther->owner_->getShape() );

    // �Փ˂����o������A�Փˌ�̏������Ăяo��
    if( is_collided )
    {
        auto function = post_collision_.find( pOther->owner_->getID() );
        if( function != post_collision_.end() )
        {
            function->second( pOther->owner_ );
        }
    }

    return is_collided;
}
END_EGEG
// EOF
