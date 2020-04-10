// �쐬�� : ��
#include "easy_engine.hpp"
#include "platform_factory.hpp"
#include "system_manager.hpp"
#include "rendering_manager.hpp"
#include "shader_manager.hpp"
#include "texture_manager.hpp"

#include "game.hpp"

BEGIN_EGEG
#ifdef _DEBUG
int EasyEngine::create_cnt_;
#endif // !_DEBUG

// EasyEngine
/*===========================================================================*/
// ���s
void EasyEngine::run( const std::string& Platform )
{
    // �e��C���^�[�t�F�C�X�̐���
    IPlatform* p_platform;
    if( PlatformFactory::instance()->create(Platform, &p_platform) == false )
        return;
    IRenderer* p_renderer;
    if( p_platform->createRenderer(&p_renderer) == false ) return;
    IShaderLoader* p_shader_loader;
    if( p_platform->createShaderLoader(&p_shader_loader) == false ) return;
    ITextureLoader* p_texture_loader;
    if( p_platform->createTextureLoader(&p_texture_loader) == false ) return;

    // �C���^�[�t�F�C�X�̊Ǘ����}�l�[�W���[�Ɉϑ�
    SystemManager::create( *this, p_platform );
    RenderingManager::create( *this, p_renderer );
    ShaderManager::create( *this, p_shader_loader );
    TextureManager::create( *this, p_texture_loader );

    // �Q�[�����s
    Game game;
    if( game.initialize() == false ) return;
    SystemManager::instance()->mainLoop( std::extraction(&Game::update, &game, std::placeholders::_1) );
    game.finalize();

    // �}�l�[�W���[��j��
    TextureManager::destroy( *this );
    ShaderManager::destroy( *this );
    RenderingManager::destroy( *this );
    SystemManager::destroy( *this );
}
END_EGEG
// EOF
