// �쐬�� : ��
#include "sprite_component.hpp"
#include "render_batch.hpp"

BEGIN_EGEG
// SpriteComponent : �֐��̎���
/*===========================================================================*/
// �X�v���C�g���̃Z�b�g
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
    // ��񂩂烂�f���𐶐�


    visible_ = true;
}

// �`��
void SpriteComponent::render()
{
    if( visible_ )
    {

    }
}

// ����������
bool SpriteComponent::initialize()
{
    visible_ = false;
    RenderBatch::instance()->registerComponent( this );

    return true;
}

// �I������
void SpriteComponent::finalize()
{
    RenderBatch::instance()->unregisterComponent( this );
}
END_EGEG
// EOF
