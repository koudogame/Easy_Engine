// �쐬�� : ��
#include "render_batch.hpp"
#include "render_component.hpp"

BEGIN_EGEG
// RenderBatch : �֐��̎���
/*===========================================================================*/
// �o�b�`����
void RenderBatch::render()
{
    for( auto& component : components_ )
    {
        component->render();
    }
}
END_EGEG
// EOF