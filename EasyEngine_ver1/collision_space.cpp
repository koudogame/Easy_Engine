// 作成者 : 板場
#include "collision_space.hpp"

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
END_EGEG
// EOF
