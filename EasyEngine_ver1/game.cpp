// �쐬�� : ��
#include "game.hpp"
#include "job_scheduler.hpp"
#include "render_batch.hpp"

BEGIN_EGEG
// Game : �֐��̎���
/*===========================================================================*/
// ����������
bool Game::initialize()
{


    return true;
}

// �I������
void Game::finalize()
{

}

// �X�V����
void Game::update( uint64_t Delta )
{
    JobScheduler::instance()->execute( Delta );
    RenderBatch::instance()->render();
}
END_EGEG
// EOF
