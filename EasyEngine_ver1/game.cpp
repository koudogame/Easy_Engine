// 作成者 : 板場
#include "game.hpp"
#include "job_scheduler.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"

#include "texture_manager.hpp"
#include "sprite_component.hpp"

BEGIN_EGEG
// Game : 関数の実装
/*===========================================================================*/
// 初期化処理
bool Game::initialize()
{
    return true;
}

// 終了処理
void Game::finalize()
{

}

// 更新処理
bool Game::update( uint64_t Delta )
{
    JobScheduler::instance()->execute( Delta );
    RenderingManager::instance()->beginRender( { 1.0F, 1.0F, 1.0F, 1.0F} );
    RenderBatch::instance()->render();
    RenderingManager::instance()->endRender();

    return true;
}
END_EGEG
// EOF
