// 作成者 : 板場
#include "easy_engine.hpp"
#include "platform_factory.hpp"
#include "rendering_manager.hpp"
#include "shader_manager.hpp"
#include "texture_manager.hpp"

BEGIN_EGEG
#ifdef _DEBUG
int EasyEngine::create_cnt_;
#endif // !_DEBUG

// EasyEngine : 関数の実装
/*===========================================================================*/
// 実行
void EasyEngine::run( const char* Platform )
{
    // エンジンの初期化
    IPlatform* p_platform;
    if( PlatformFactory::instance()->create(Platform, &p_platform) == false )
        return;
    IRenderer* p_renderer = p_platform->getRenderer();
    IShaderLoader* p_shader_loader = p_platform->getShaderLoader();
    ITextureLoader* p_texture_loader = p_platform->getTextureLoader();

    RenderingManager::create( this, p_renderer );
    p_renderer->release();
    ShaderManager::create( this, p_shader_loader );
    p_shader_loader->release();
    TextureManager::create( this, p_texture_loader );
    p_texture_loader->release();

    // ゲーム実行

    // エンジン終了
    TextureManager::destroy( this );
    ShaderManager::destroy( this );
    RenderingManager::destroy( this );

    p_platform->release();
}
END_EGEG
// EOF
