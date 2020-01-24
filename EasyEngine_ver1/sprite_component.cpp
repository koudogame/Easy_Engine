// �쐬�� : ��
#include "sprite_component.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"
#include "shader_manager.hpp"

namespace
{
    constexpr char kSpriteVertexShaderPath[] = "sprite_vs.cso";  // �R���p�C���ς� ���_�V�F�[�_�[�t�@�C���p�X
    constexpr char kSpritePixelShaderPath[] = "sprite_ps.cso";   // �R���p�C���ς� �s�N�Z���V�F�[�_�\�t�@�C���p�X
} // !unnamed namespace


BEGIN_EGEG
// SpriteComponent : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
SpriteComponent::SpriteComponent()
{
}   

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
    // �e�N�X�`���̃Z�b�g
    pTexture->addRef();
    if( sprite_.texture ) { sprite_.texture->release(); }
    sprite_.texture = pTexture;

    // ���_���W�̐ݒ�
    const float kLeft = 0.0F;
    const float kTop  = 0.0F;
    const float kRight = static_cast<float>(pTexture->getWidth());
    const float kBottom = static_cast<float>(pTexture->getHeight());
    Mesh& mesh = sprite_.mesh;
    mesh.vertices[0].position = Vector3D{ kLeft, kTop, Depth };       // ����
    mesh.vertices[1].position = Vector3D{ kRight, kTop, Depth };      // �E��
    mesh.vertices[2].position = Vector3D{ kLeft, kBottom, Depth };    // ����
    mesh.vertices[3].position = Vector3D{ kRight, kBottom, Depth };   // �E��

    // ���_���W�̕ϊ�
    const Matrix3x3 kTranslation   = Matrix3x3::createTranslationMatrix( Position );
    const Matrix3x3 kRotarion      = Matrix3x3::createRotationMatrix( RotationDEG );
    const Matrix3x3 kScaling       = Matrix3x3::createScalingMatrix( Scale );
    const Matrix3x3 kRevOrigin     = Matrix3x3::createTranslationMatrix( Origin * -1.0F );
    const Matrix3x3 kTransform     = kTranslation * kRotarion * kScaling * kRevOrigin;
    for( auto& vertex : mesh.vertices )
    {
        vertex.position = kTransform * vertex.position;
    }

    // ���_���W�̐��K��
    const Vector2D kScreenSize = RenderingManager::instance()->getScreenSize();
    const float kXCoefficient = (0.5F / kScreenSize.x );
    const float kYCoefficient = -(0.5F / kScreenSize.y );
    for( auto& vertex : mesh.vertices )
    {
        vertex.position.x = (vertex.position.x * kXCoefficient) - 1.0F;
        vertex.position.y = (vertex.position.y * kYCoefficient) - 1.0F;
    }

    // UV���W�̐ݒ�
    const float kRecWidth  = 1.0F / pTexture->getWidth();
    const float kRecHeight = 1.0F / pTexture->getHeight();
    const float kUVLeft   = Trimming.x * kRecWidth;
    const float kUVRight  = Trimming.z * kRecWidth;
    const float kUVTop    = Trimming.y * kRecHeight;
    const float kUVBottom = Trimming.w * kRecHeight;
    mesh.vertices[0].uv = { kUVLeft, kUVTop };
    mesh.vertices[1].uv = { kUVRight, kUVTop };
    mesh.vertices[2].uv = { kUVLeft, kUVBottom };
    mesh.vertices[3].uv = { kUVRight, kUVBottom };

    // ���_�J���[�̃Z�b�g
    for( auto& vertex : mesh.vertices )
    {
        vertex.color_rgba = { Color.x, Color.y, Color.z, Alpha };
    }

    visible_ = true;
    validity_ = true;
}

// �`��
void SpriteComponent::render()
{
    if( validity_ && visible_ )
    {
        RenderingManager::instance()->render( sprite_ );
    }
}

// ����������
bool SpriteComponent::initialize()
{
    validity_ = false;
    visible_ = false;
    sprite_.mesh.vertices.reserve( 4U );
    sprite_.mesh.indices.reserve( 2U );
    sprite_.mesh.indices[0] = { 0, 1, 2 };
    sprite_.mesh.indices[1] = { 1, 3, 2 };

    // �V�F�[�_�[�̃��[�h
    if( ShaderManager::instance()->loadVertexShader(::kSpriteVertexShaderPath, &sprite_.vertex_shader) == false )
        return false;
    if( ShaderManager::instance()->loadPixelShader(::kSpritePixelShaderPath, &sprite_.pixel_shader) == false )
        return false;
    sprite_.geometry_shader = nullptr;

    // �����l�̐ݒ�
    sprite_.texture = nullptr;

    // �R���|�[�l���g�̓o�^
    RenderBatch::instance()->registerComponent( this );

    validity_ = true;
    return true;
}

// �I������
void SpriteComponent::finalize()
{
    // �e�N�X�`���̊J��
    if( sprite_.texture ) { sprite_.texture->release(); }

    // �R���|�[�l���g�̓o�^����
    RenderBatch::instance()->unregisterComponent( this );

    // �V�F�[�_�[�̃A�����[�h
    ShaderManager::instance()->unloadPixelShader( &sprite_.pixel_shader );
    ShaderManager::instance()->unloadVertexShader( &sprite_.vertex_shader );

}
END_EGEG
// EOF
