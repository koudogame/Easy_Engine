// ì¬ŽÒ : ”Âê
#include "game.hpp"
#include "job_scheduler.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"

#include "texture_manager.hpp"
#include "sprite_component.hpp"

BEGIN_EGEG
// Game : ŠÖ”‚ÌŽÀ‘•
/*===========================================================================*/
// ‰Šú‰»ˆ—
bool Game::initialize()
{
   if( sprite.initialize() == false ) return false;

    if( TextureManager::instance()->load( L"tile.png", &texture_) == false )
        return false;

    return true;
}

// I—¹ˆ—
void Game::finalize()
{
    TextureManager::instance()->unload( &texture_ );
   sprite.finalize();
}

// XVˆ—
bool Game::update( uint64_t Delta )
{
    sprite.setStatus(
        texture_,
        {0.0F, 0.0F},
        {0.0F, 0.0F, 64.0F, 64.0F});

    JobScheduler::instance()->execute( Delta );
    RenderingManager::instance()->beginRender( { 0.0F, 0.0F, 0.0F, 1.0F} );
    RenderBatch::instance()->render();
    RenderingManager::instance()->endRender();

    return true;
}
END_EGEG
// EOF
