// 作成者 : 板場
#include "actor.hpp"
#include "component.hpp"

BEGIN_EGEG
// Actor : 関数の実装
/*===========================================================================*/
// デストラクタ
Actor::~Actor()
{
    // 保持しているコンポーネントの解放
    for( auto& component : components_ )
    {
        component.second->finalize();
        delete component.second;
    }
}
END_EGEG
// EOF
