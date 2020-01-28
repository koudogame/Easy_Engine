// �쐬�� : ��
#include "render_component.hpp"
#include "render_batch.hpp"

BEGIN_EGEG
// RenderComponent : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
RenderComponent::RenderComponent()
{
    RenderBatch::instance()->registerComponent( this );
}
// �f�X�g���N�^
RenderComponent::~RenderComponent()
{
    RenderBatch::instance()->unregisterComponent( this );
}

// �`��X�e�[�^�X�ݒ�
void RenderComponent::setVisible( bool Visible )
{
    if( Visible )
        RenderBatch::instance()->registerComponent( this );
    else
        RenderBatch::instance()->unregisterComponent( this );
}
END_EGEG
// EOF
