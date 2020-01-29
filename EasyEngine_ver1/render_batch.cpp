// ì¬ŽÒ : ”Âê
#include "render_batch.hpp"
#include "render_component.hpp"

BEGIN_EGEG
// RenderBatch : ŠÖ”‚ÌŽÀ‘•
/*===========================================================================*/
// ƒoƒbƒ`ˆ—
void RenderBatch::render()
{
    for( auto& component : components_ )
    {
        component->render();
    }
}
END_EGEG
// EOF
