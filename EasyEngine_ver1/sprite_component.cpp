// 作成者 : 板場
#include "sprite_component.hpp"
#include "render_batch.hpp"

BEGIN_EGEG
// SpriteComponent : 関数の実装
/*===========================================================================*/
// スプライト情報のセット
void SpriteComponent::setStatus(
    ITexture* pTexture,
    const Vector2D& Position,
    const Vector4D& Trimming,
    float RotationDEG,
    const Vector2D& Scale,
    const Vector2D& Origin,
    const Vector3D& Color,
    float Alpha,
    float Depth )
{
    // 情報からモデルを生成


    visible_ = true;
}

// 描画
void SpriteComponent::render()
{
    if( visible_ )
    {

    }
}

// 初期化処理
bool SpriteComponent::initialize()
{
    visible_ = false;
    RenderBatch::instance()->registerComponent( this );

    return true;
}

// 終了処理
void SpriteComponent::finalize()
{
    RenderBatch::instance()->unregisterComponent( this );
}
END_EGEG
// EOF
