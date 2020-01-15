// �쐬�� : ��
#include "rendering_manager.hpp"

BEGIN_EGEG
RenderingManager* RenderingManager::instance_;

// RenderingManager : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
RenderingManager::RenderingManager( IRenderer* pRenderer ) :
    p_renderer_( pRenderer )
{
    p_renderer_->addRef();
}
// �f�X�g���N�^
RenderingManager::~RenderingManager()
{
    p_renderer_->release();
}

// �`��J�n
void RenderingManager::beginRender( const Vector4D& Color )
{
    p_renderer_->beginRender( Color );
}

// �`��̃G���g���[
void RenderingManager::entryRender( const Model& Model )
{
    p_renderer_->entryRender( Model );
}
void RenderingManager::entryRender( const Mesh& Mesh, ITexture* pTexture, IVertexShader* pVertexShader, IGeometryShader* pGeometryShader, IPixelShader* pPixelShader )
{
    Model model =
    {
        model.mesh = Mesh,
        model.texture = pTexture,
        model.vertex_shader = pVertexShader,
        model.geometry_shader = pGeometryShader,
        model.pixel_shader = pPixelShader
    };
    this->entryRender( model );
}

// �`��I��
void RenderingManager::endRender()
{
    p_renderer_->endRender();
}

// �C���X�^���X�̐���
void RenderingManager::create( const EasyEngine* pCreator, IRenderer* pRenderer )
{
    pCreator->proof();

    destroy( pCreator );
    instance_ = new RenderingManager( pRenderer );
}
// �C���X�^���X�̔j��
void RenderingManager::destroy( const EasyEngine* pDeleter )
{
    pDeleter->proof();

    if( instance_ )
    {
        delete instance_;
        instance_ = nullptr;
    }
}
END_EGEG
// EOF
