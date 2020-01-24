// 作成者 : 板場
#include "rendering_manager.hpp"

BEGIN_EGEG
RenderingManager* RenderingManager::instance_;

// RenderingManager
/*===========================================================================*/
// コンストラクタ
RenderingManager::RenderingManager( IRenderer* pRenderer ) :
    p_renderer_( pRenderer )
{
}
// デストラクタ
RenderingManager::~RenderingManager()
{
    delete p_renderer_;
}

// 描画開始
void RenderingManager::beginRender( const Vector4D& Color )
{
    batch_list_.clear();
    p_renderer_->clear( Color );
}

// 描画のエントリー
void RenderingManager::render( const Model& Model )
{
    batch_list_.push_back( Model );
}
void RenderingManager::render( const Mesh& Mesh, ITexture* pTexture, IVertexShader* pVertexShader, IGeometryShader* pGeometryShader, IPixelShader* pPixelShader )
{
    Model model =
    {
        model.mesh = Mesh,
        model.texture = pTexture,
        model.vertex_shader = pVertexShader,
        model.geometry_shader = pGeometryShader,
        model.pixel_shader = pPixelShader
    };
    this->render( model );
}

// 描画終了
void RenderingManager::endRender()
{
    for( auto& model : batch_list_ )
    {
        p_renderer_->renderModel( model );
    }
    batch_list_.clear();
}

// インスタンスの生成
void RenderingManager::create( const EasyEngine& Creator, IRenderer* pRenderer )
{
    destroy( Creator );
    instance_ = new RenderingManager( pRenderer );
}
// インスタンスの破棄
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
