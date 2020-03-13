// �쐬�� : ��
#include "sprite_component.hpp"
#include "render_batch.hpp"
#include "system_manager.hpp"
#include "rendering_manager.hpp"
#include "texture_manager.hpp"
#include "shader_manager.hpp"

namespace
{
    enum VertexPosition
    {
        kTopLeft,
        kTopRight,
        kBottomLeft,
        kBottomRight
    };

    constexpr char kVertexShaderPath[] = "sprite_vs.cso";  // �R���p�C���ς� ���_�V�F�[�_�[�t�@�C���p�X
    constexpr char kPixelShaderPath[] = "sprite_ps.cso";   // �R���p�C���ς� �s�N�Z���V�F�[�_�\�t�@�C���p�X
} // !unnamed namespace


BEGIN_EGEG
// SpriteComponent : public �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
SpriteComponent::SpriteComponent( Actor* Owner ) :
    RenderComponent( Owner ),
    is_validity_( false )   // �������������Ăяo�����O�ɕ`�悳��邱�Ƃ�h��
{
}   

#if true
// �X�v���C�g���̃Z�b�g
void SpriteComponent::setStatus( 
    ITexture* pTexture, 
    const Vector2D& Position, 
    const Vector4D& Trimming,
    float AngleDEG, 
    const Vector2D& Scale, 
    const Vector2D& Origin, 
    const Vector3D& Color,
    float Alpha, 
    float Depth )
{
    setTexture( pTexture );
    setPosition( Position );
    setTrimming( Trimming );
    setScale( Scale );
    setOrigin( Origin );
    setColor( Color );
    setAlpha( Alpha );
    setDepth( Depth );
}

// �e�N�X�`���̃Z�b�g
void SpriteComponent::setTexture( ITexture* pTexture )
{
    pTexture->addRef();

    // ���ɂ���e�N�X�`�����������
    if( p_texture_ ) TextureManager::instance()->unload( &p_texture_ );

    p_texture_ = pTexture;
}

// ����������
bool SpriteComponent::initialize()
{
    // �V�F�[�_�[�̓ǂݍ���
    if( ShaderManager::instance()->loadVertexShader(::kVertexShaderPath, &p_vertex_shader_) == false )
    {
        std::string err = "�V�F�[�_�[�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n";
        err += "�t�@�C�� : ";
        err += ::kVertexShaderPath;
        err += "\n\n�ꏊ : SpriteComponent::initialize";

        SystemManager::instance()->showDialogBox( err );
        return false;
    }
    if( ShaderManager::instance()->loadPixelShader(::kPixelShaderPath, &p_pixel_shader_) == false )
    {
        std::string err = "�V�F�[�_�[�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n";
        err += "�t�@�C�� : ";
        err += ::kPixelShaderPath;
        err += "\n\n�ꏊ : SpriteComponent::initialize";

        SystemManager::instance()->showDialogBox( err );
        return false;
    }


    // ����I��
    is_visible_ = true;
    is_validity_ = true;
    return true;
}

// �I������
void SpriteComponent::finalize()
{
    ShaderManager::instance()->unloadVertexShader( &p_vertex_shader_ );
    ShaderManager::instance()->unloadPixelShader( &p_pixel_shader_ );
}

// �`�揈��
void SpriteComponent::render()
{
    if( is_validity_ == false || is_visible_ == false ) 
        return;

    // ���f����`��
    Model sprite;
    sprite.mesh.vertices.reserve( 4U ); // 4���_
    sprite.mesh.indices.reserve( 2U );  // 2�|���S��
    getModelStatus( &sprite );
    RenderingManager::instance()->renderModel( sprite );
}

// SpriteComponent : private �֐��̎���
/*===========================================================================*/
// ���f���̏�Ԃ��擾
// ���̊֐��Ăяo�������_�ł́A�X�v���C�g��񂩂烂�f���̏�Ԃ����肵�܂��B
//
// out pModel : ��Ԃ��擾���郂�f���̃A�h���X
void SpriteComponent::getModelStatus( Model* pModel )
{
    // ���_�f�[�^�̐ݒ�
    Vector3D position[4];
    getVerticesPositoin( position );
    Vector2D uv[4];
    getVerticesUV( uv );
    for( int i = 0; i < 4; ++i )
    {
        pModel->mesh.vertices.push_back(
            { /*position[i],*/ uv[i], color_ }
        );
    }
    
    // ���_�C���f�b�N�X�̐ݒ�
    pModel->mesh.indices.push_back( { ::kTopLeft, ::kTopRight, ::kBottomLeft } );
    pModel->mesh.indices.push_back( { ::kTopRight, ::kBottomRight, ::kBottomLeft } );

    // �e�N�X�`���̐ݒ�
    pModel->texture = p_texture_;

    // �V�F�[�_�[�̐ݒ�
    pModel->vertex_shader = p_vertex_shader_;
    pModel->geometry_shader = nullptr;
    pModel->pixel_shader = p_pixel_shader_;
}

// ���_���W���擾
//
// out arrPosition[4] : ��Ԃ��擾����z��
void SpriteComponent::getVerticesPositoin( Vector3D arrPosition[4] )
{
    // �؂���͈͂���傫�����Z�o
    const float kLeft   = 0.F;
    const float kTop    = 0.F;
    const float kRight  = trimming_.z - trimming_.x;
    const float kBottom = trimming_.w - trimming_.y;
    arrPosition[::kTopLeft]     = { kLeft,  kTop, 1.F };
    arrPosition[::kTopRight]    = { kRight, kTop, 1.F };
    arrPosition[::kBottomLeft]  = { kLeft,  kBottom, 1.F };
    arrPosition[::kBottomRight] = { kRight, kBottom, 1.F };

    // �ϊ��s��̍쐬
    const Matrix3x3 kTranslation = Matrix3x3::createTranslationMatrix( position_ );
    const Matrix3x3 kRotation    = Matrix3x3::createRotationMatrix( rotation_ );
    const Matrix3x3 kScaling     = Matrix3x3::createScalingMatrix( scale_ );
    const Matrix3x3 kRevOrigin   = Matrix3x3::createTranslationMatrix( origin_ * -1.F );
    const Matrix3x3 kTransform = kTranslation * kRotation * kScaling * kRevOrigin;
 
    // ���W�̕ϊ������K��
    const Vector2D kScreenSize = RenderingManager::instance()->getScreenSize();
    const float kCoefficientX = 2.F / kScreenSize.x;
    const float kCoefficientY = -2.0F / kScreenSize.y;
    for( int i = 0; i < 4; ++i )
    {
        arrPosition[i] = kTransform * arrPosition[i];
        arrPosition[i].x = arrPosition[i].x * kCoefficientX - 1.F;
        arrPosition[i].y = arrPosition[i].y * kCoefficientY + 1.F;
    }
}

// ���_UV���W���擾
//
//out arrUV[4] : ��Ԃ��擾����z��
void SpriteComponent::getVerticesUV( Vector2D arrUV[4] )
{
    const float kRecWidth  = 1.F / p_texture_->getWidth();  // ����Z�̐������炷����
    const float kRecHeight = 1.F / p_texture_->getHeight(); // ����Z�̐������炷����
     
    const float kLeft   = trimming_.x * kRecWidth;
    const float kRight  = trimming_.z * kRecWidth;
    const float kTop    = trimming_.y * kRecHeight;
    const float kBottom = trimming_.w * kRecHeight;
    arrUV[::kTopLeft]     = { kLeft, kTop };
    arrUV[::kTopRight]    = { kRight, kTop };
    arrUV[::kBottomLeft]  = { kLeft, kBottom };
    arrUV[::kBottomRight] = { kRight, kBottom };
}
#else
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
    if( p_texture ) { sprite_.texture->release(); }
    sprite_.texture = pTexture;

    Vector3D vertices[4];
    const float Width  = Trimming.z - Trimming.x;
    const float Height = Trimming.w - Trimming.y;

    // ���_���W�̐ݒ�
    const float kLeft = 0.0F;
    const float kTop  = 0.0F;
    const float kRight = Width;
    const float kBottom = Height;
    vertices[0] = Vector3D{ kLeft, kTop, 1.0F };       // ����
    vertices[1] = Vector3D{ kRight, kTop, 1.0F };      // �E��
    vertices[2] = Vector3D{ kLeft, kBottom, 1.0F };    // ����
    vertices[3] = Vector3D{ kRight, kBottom, 1.0F };   // �E��
    // ���_���W�̕ϊ�
    const Matrix3x3 kTranslation   = Matrix3x3::createTranslationMatrix( Position );
    const Matrix3x3 kRotarion      = Matrix3x3::createRotationMatrix( RotationDEG );
    const Matrix3x3 kScaling       = Matrix3x3::createScalingMatrix( Scale );
    const Matrix3x3 kRevOrigin     = Matrix3x3::createTranslationMatrix( Origin * -1.0F );
    const Matrix3x3 kTransform     = kTranslation * kRotarion * kScaling * kRevOrigin;
    for( auto& vertex : vertices )
    {
        vertex = kTransform * vertex;
        vertex.z = Depth;
    }
    // ���_���W�̐��K��
    const Vector2D kScreenSize = RenderingManager::instance()->getScreenSize();
    const float kXCoefficient = (2.0F / kScreenSize.x );
    const float kYCoefficient = -(2.0F / kScreenSize.y );
    for( auto& vertex : vertices )
    {
        vertex.x = (vertex.x * kXCoefficient) - 1.0F;
        vertex.y = (vertex.y * kYCoefficient) + 1.0F;
    }

    // UV���W�̐ݒ�
    Float2 uv[4];
    const float kRecWidth  = 1.0F / pTexture->getWidth();
    const float kRecHeight = 1.0F / pTexture->getHeight();
    const float kUVLeft   = Trimming.x * kRecWidth;
    const float kUVRight  = Trimming.z * kRecWidth;
    const float kUVTop    = Trimming.y * kRecHeight;
    const float kUVBottom = Trimming.w * kRecHeight;
    uv[0] = { kUVLeft, kUVTop };
    uv[1] = { kUVRight, kUVTop };
    uv[2] = { kUVLeft, kUVBottom };
    uv[3] = { kUVRight, kUVBottom };

    // ���_�Z�b�g
    sprite_.mesh.vertices.clear();
    for( int i = 0; i < 4; ++i )
    {
        sprite_.mesh.vertices.push_back(
            VertexData {
                vertices[i],
                uv[i],
                { Color.x, Color.y, Color.z, Alpha }
            }
        );
    }

    visible_ = true;
    validity_ = true;
}

// �`��
void SpriteComponent::render()
{
    if( validity_ && visible_ )
    {
        RenderingManager::instance()->renderModel( sprite_ );
    }
}

// ����������
bool SpriteComponent::initialize()
{
    // �����l�̐ݒ�
    validity_ = false;
    visible_ = false;
    sprite_.mesh.vertices.reserve( 4U );
    sprite_.mesh.indices.reserve( 2U );
    sprite_.mesh.indices.push_back( { 0, 1, 2 } );
    sprite_.mesh.indices.push_back( { 1, 3, 2 } );
    sprite_.texture = nullptr;

    // �V�F�[�_�[�̐ݒ�
    if( ShaderManager::instance()->loadVertexShader(::kSpriteVertexShaderPath, &sprite_.vertex_shader) == false )
        return false;
    if( ShaderManager::instance()->loadPixelShader(::kSpritePixelShaderPath, &sprite_.pixel_shader) == false )
        return false;
    sprite_.geometry_shader = nullptr;

    // �R���|�[�l���g�̓o�^
    RenderBatch::instance()->registerComponent( this );

    validity_ = true;
    return true;
}

// �I������
void SpriteComponent::finalize()
{
    // �R���|�[�l���g�̓o�^����
    RenderBatch::instance()->unregisterComponent( this );

    // ���\�[�X�̃A�����[�h
    TextureManager::instance()->unload( &sprite_.texture );
    ShaderManager::instance()->unloadPixelShader( &sprite_.pixel_shader );
    ShaderManager::instance()->unloadVertexShader( &sprite_.vertex_shader );
}
#endif
END_EGEG
// EOF
