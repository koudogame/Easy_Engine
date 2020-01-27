// �쐬�� : ��
#include "rendering_manager.hpp"

BEGIN_EGEG
RenderingManager* RenderingManager::instance_;

// RenderingManager
/*===========================================================================*/
// �R���X�g���N�^
RenderingManager::RenderingManager( IRenderer* pRenderer ) :
    p_renderer_( pRenderer )
{
}
// �f�X�g���N�^
RenderingManager::~RenderingManager()
{
    delete p_renderer_;
}

// �`��J�n
void RenderingManager::beginRender( const Vector4D& Color )
{
    p_renderer_->beginRender();
    p_renderer_->clear( Color );
}

// �`��̃G���g���[
void RenderingManager::renderModel( const Model& Model )
{
    p_renderer_->renderModel( Model );
}
void RenderingManager::renderModel( const Mesh& Mesh, ITexture* pTexture, IVertexShader* pVertexShader, IGeometryShader* pGeometryShader, IPixelShader* pPixelShader )
{
    Model model =
    {
        model.mesh = Mesh,
        model.texture = pTexture,
        model.vertex_shader = pVertexShader,
        model.geometry_shader = pGeometryShader,
        model.pixel_shader = pPixelShader
    };
    this->renderModel( model );
}

// �`��I��
void RenderingManager::endRender()
{
    p_renderer_->endRender();
}

// �C���X�^���X�̐���
void RenderingManager::create( const EasyEngine& Creator, IRenderer* pRenderer )
{
    destroy( Creator );
    instance_ = new RenderingManager( pRenderer );
}
// �C���X�^���X�̔j��
void RenderingManager::destroy( const EasyEngine& Deleter )
{
    Deleter.proof();

    if( instance_ )
    {
        delete instance_;
        instance_ = nullptr;
    }
}
END_EGEG
// EOF
