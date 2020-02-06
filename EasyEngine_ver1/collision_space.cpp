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

        // 次に判定を行うセクションへと移行
        curr_section = nextJudgeSection( curr_section );
        if( curr_section != nullptr )
        {
            to_judge_sections.push_back( curr_section );
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
//
// in Sec1 : セクション1
// in Sec2 : セクション2
void CollisionSpace::judgeSectionAndSection( CollisionSection* Sec1, CollisionSection* Sec2 )
{
    while( auto sec1_com = Sec1->pickComponent() )
    {
        while( auto sec2_com = Sec2->pickComponent() )
        {
            // 衝突
            if( (sec1_com != sec2_com) &&
                (sec1_com->getShape()->isCollided(sec2_com->getShape())) ) 
            {
                sec1_com->notifyCollision( sec2_com );
                sec2_com->notifyCollision( sec1_com );
            }
        }
    }
}

// 現在のセクションから、次に衝突を検出するセクションを取得
//
// in CurrSection : 現在のセクション
//
// return 次に衝突を検出するセクション
CollisionSection* nextJudgeSection( CollisionSection* CurrSection )
{
    CollisionSection* curr = CurrSection;
    CollisionSection* next = curr->pickChild();
    while( next == nullptr )
    {
        // 子がいない場合親方向へ一つ戻る
        curr = CurrSection->getParent();
        if( curr == nullptr ) break;

        next = curr->pickChild();
    }

    return next;
}
END_EGEG
// EOF
