// ì¬ŽÒ : ”Âê
#include "game.hpp"
#include "job_scheduler.hpp"
#include "render_batch.hpp"

BEGIN_EGEG
// Game : ŠÖ”‚ÌŽÀ‘•
/*===========================================================================*/
// ‰Šú‰»ˆ—
bool Game::initialize()
{


    return true;
}

// I—¹ˆ—
void Game::finalize()
{

}

// XVˆ—
void Game::update( uint64_t Delta )
{
    JobScheduler::instance()->execute( Delta );
    RenderBatch::instance()->render();
}
END_EGEG
// EOF
