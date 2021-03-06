// 作成者 : 板場
#include "game.hpp"
#include "job_scheduler.hpp"
#include "scene_manager.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"
#include "uid.hpp"
#include "entry_scene.hpp"

BEGIN_EGEG
// Game : 関数の実装
/*===========================================================================*/
// 初期化処理
bool Game::initialize()
{
    SceneManager::instance()->push( TypeID<EntryScene>::getID() );
    return true;
}

// 終了処理
void Game::finalize()
{
    SceneManager::instance()->destroy();
}

// 更新処理
bool Game::update( uint64_t Delta )
{
    JobScheduler::instance()->execute( Delta );
    RenderingManager::instance()->beginRender( { 0.5F, .5F, 0.5F, 1.0F} );
    RenderBatch::instance()->render();
    RenderingManager::instance()->endRender();

    return true;
}
END_EGEG
// EOF
