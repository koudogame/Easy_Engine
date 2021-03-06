// 作成者 : 板場
#include "render_batch.hpp"
#include "render_component.hpp"

BEGIN_EGEG
// RenderBatch : 関数の実装
/*===========================================================================*/
// バッチ処理
void RenderBatch::render()
{
    for( auto& component : components_ )
    {
        component->render();
    }
}
END_EGEG
// EOF
