// �쐬�� : ��
#include "collision_section.hpp"


BEGIN_EGEG
// CollisionSection : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
CollisionSection::CollisionSection()
{
    components_.push_back( nullptr );   // �擪�Ƀ_�~�[�����Ă���(��̎����C�e���[�^�[��L���ɂ��邽��)
    component_itr_ = components_.begin();
}

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
    if( curr_idx >= childs_.size() )
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
    ++component_itr_;

    // �S�đ��������ꍇ
    if( component_itr_ == components_.end() )
    {
        component_itr_ = components_.begin();
        return nullptr;
    }

    return *component_itr_;
}
END_EGEG
// EOF
