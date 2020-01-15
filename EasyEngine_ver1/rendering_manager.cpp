// 作成者 : 板場
#include "rendering_manager.hpp"

BEGIN_EGEG
RenderingManager* RenderingManager::instance_;

// RenderingManager : 関数の実装
/*===========================================================================*/
// コンストラクタ
RenderingManager::RenderingManager( IRenderer* pRenderer ) :
    p_renderer_( pRenderer )
{
    p_renderer_->addRef();
}
// デストラクタ
RenderingManager::~RenderingManager()
{
    p_renderer_->release();
}

// 描画開始
void RenderingManager::beginRender( const Vector4D& Color )
{
    p_renderer_->beginRender( Color );
}

// 描画のエントリー
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

// 描画終了
void RenderingManager::endRender()
{
    p_renderer_->endRender();
}

// インスタンスの生成
void RenderingManager::create( const EasyEngine* pCreator, IRenderer* pRenderer )
{
    pCreator->proof();

    destroy( pCreator );
    instance_ = new RenderingManager( pRenderer );
}
// インスタンスの破棄
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
