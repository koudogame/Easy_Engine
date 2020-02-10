// 作成者 : 板場
#include "collision_section.hpp"


BEGIN_EGEG
// CollisionSection : 関数の実装
/*===========================================================================*/
// コンストラクタ
CollisionSection::CollisionSection()
{
    components_.push_back( nullptr );   // 先頭にダミーを入れておく(空の時もイテレーターを有効にするため)
    component_itr_ = components_.begin();
}

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

// 所属コンポーネントの選択
CollisionComponent* CollisionSection::pickComponent()
{
    ++component_itr_;

    // 全て走査した場合
    if( component_itr_ == components_.end() )
    {
        component_itr_ = components_.begin();
        return nullptr;
    }

    return *component_itr_;
}
END_EGEG
// EOF
