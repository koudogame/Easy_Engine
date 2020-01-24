// 作成者 : 板場
#include "game.hpp"
#include "job_scheduler.hpp"
#include "render_batch.hpp"

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
void Game::update( uint64_t Delta )
{
    JobScheduler::instance()->execute( Delta );
    RenderBatch::instance()->render();
}
END_EGEG
// EOF
