// 作成者 : 板場
#include "easy_engine.hpp"
#include "platform_factory.hpp"
#include "rendering_manager.hpp"
#include "shader_manager.hpp"
#include "texture_manager.hpp"

BEGIN_EGEG
// EasyEngine : 関数の実装
/*===========================================================================*/
// 実行
void EasyEngine::run( const char* Platform )
{
    // エンジンの初期化
    IPlatform* p_platform;
    if( PlatformFactory::instance()->create(Platform, &p_platform) == false )
        return;
    IRenderer* p_renderer = p_platform->createRenderer();
    IShaderLoader* p_shader_loader = p_platform->createShaderLoader();
    ITextureLoader* p_texture_loader = p_platform->createTextureLoader();

    RenderingManager::instance()->create( this, p_renderer );
    p_renderer->release();
    ShaderManager::instance()->create( this, p_shader_loader );
    p_shader_loader->release();
    TextureManager::instance()->create( this, p_texture_loader );
    p_texture_loader->release();

    // ゲーム初期化

    // ゲーム実行

    // ゲーム終了

    // エンジン終了
    TextureManager::instance()->destroy( this );
    ShaderManager::instance()->destroy( this );
    RenderingManager::instance()->destroy( this );

    p_platform->release();
}
END_EGEG
// EOF
