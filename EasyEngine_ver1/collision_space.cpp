// 作成者 : 板場
#include "collision_space.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionSpace : 関数の実装
/*===========================================================================*/
// コンストラクタ
CollisionSpace::CollisionSpace()
{
    SpatialDivision spatial_division;
    spatial_division.setSections( &sections_ );
}

// 衝突判定
void CollisionSpace::collision()
{
    std::vector<CollisionSection*> to_judge_sections;    // 判定リスト
    to_judge_sections.reserve( sections_.size() );

    
    to_judge_sections.push_back( &(*sections_.begin()) );
    CollisionSection* curr_section = to_judge_sections.back();
    while( curr_section )
    {
        // 衝突判定リストと現在のセクションの判定を行う
        for( auto& section : to_judge_sections )
        {
            judgeSectionAndSection( section, curr_section );
        }

        // 子をリストに追加
        CollisionSection* child = curr_section->pickChild();
        while( child == nullptr && curr_section )
        {
            curr_section = curr_section->getParent();
            if( curr_section == nullptr ) break;

            child = curr_section->pickChild();
        }
    }
}

// 空間への登録
void CollisionSpace::entry( CollisionComponent* pComponent )
{
    SpatialDivision spatial_division;
    uint32_t section = spatial_division.createID( pComponent->getShape() );

    sections_[section].entry( pComponent );
}
// 空間から削除
void CollisionSpace::exit( CollisionComponent* pComponent )
{
    // 所属セクションから削除
    pComponent->getBelongSection()->exit( pComponent );
}


// セクションとセクションの判定処理
void CollisionSpace::judgeSectionAndSection( CollisionSection* Sec1, CollisionSection* Sec2 )
{
    while( auto sec1_com = Sec1->pickComponent() )
    {
        while( auto sec2_com = Sec2->pickComponent() )
        {
            // 衝突
            if( sec1_com->getShape()->isCollided(sec2_com->getShape()) ) 
            {
                sec1_com->notifyCollision( sec2_com );
                sec2_com->notifyCollision( sec1_com );
            }
        }
    }
}
END_EGEG
// EOF
