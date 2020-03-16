// 作成者 : 板場
#include "actor.hpp"
#include "component.hpp"

BEGIN_EGEG

// Actor 関数定義
/*===========================================================================*/
Actor::~Actor()
{
    // コンポーネントの解放
    for( auto& component : components_ )
    {
        component.second->finalize();
        delete component.second;
    }
}

END_EGEG
// EOF
