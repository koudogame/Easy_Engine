// 作成者 : 板場
#include "render_component.hpp"
#include "render_batch.hpp"

BEGIN_EGEG
// RenderComponent : 関数の実装
/*===========================================================================*/
// コンストラクタ
RenderComponent::RenderComponent()
{
    RenderBatch::instance()->registerComponent( this );
}
// デストラクタ
RenderComponent::~RenderComponent()
{
    RenderBatch::instance()->unregisterComponent( this );
}

// 描画ステータス設定
void RenderComponent::setVisible( bool Visible )
{
    if( Visible )
        RenderBatch::instance()->registerComponent( this );
    else
        RenderBatch::instance()->unregisterComponent( this );
}
END_EGEG
// EOF
