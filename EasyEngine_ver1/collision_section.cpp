// �쐬�� : ��
#include "collision_section.hpp"


BEGIN_EGEG
// CollisionSection : �֐��̎���
/*===========================================================================*/
// �R���|�[�l���g�̒ǉ�
void CollisionSection::entry( CollisionComponent* pComponent )
{
    pComponent->setBelongSection( this );
    components_.push_back( pComponent );
}
// �R���|�[�l���g�̍폜
void CollisionSection::exit( CollisionComponent* pComponent )
{
    components_.remove( pComponent );
    pComponent->setBelongSection( nullptr );
}

// �q�Z�N�V�����̑I��
CollisionSection* CollisionSection::pickChild()
{
    uint32_t curr_idx = child_idx_++;
    
    // �ꏄ
    if( curr_idx > childs_.size() )
    {
        child_idx_ = 0U;
        return nullptr;
    }
    else
    {
        return childs_.at( curr_idx );
    }
}

// �����R���|�[�l���g�̑I��
CollisionComponent* CollisionSection::pickComponent()
{
    auto curr_itr = component_itr_++;

    // �ꏄ
    if( curr_itr == components_.end() )
    {
        component_itr_ = components_.begin();
        return nullptr;
    }
    else
    {
        return *curr_itr;
    }
}
END_EGEG
// EOF
