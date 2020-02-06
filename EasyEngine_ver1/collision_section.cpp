// 作成者 : 板場
#include "collision_section.hpp"


BEGIN_EGEG
// CollisionSection : 関数の実装
/*===========================================================================*/
// コンポーネントの追加
void CollisionSection::entry( CollisionComponent* pComponent )
{
    pComponent->setBelongSection( this );
    components_.push_back( pComponent );
}
// コンポーネントの削除
void CollisionSection::exit( CollisionComponent* pComponent )
{
    components_.remove( pComponent );
    pComponent->setBelongSection( nullptr );
}

// 子セクションの選択
CollisionSection* CollisionSection::pickChild()
{
    uint32_t curr_idx = child_idx_++;
    
    // 一巡
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

// 所属コンポーネントの選択
CollisionComponent* CollisionSection::pickComponent()
{
    auto curr_itr = component_itr_++;

    // 一巡
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
