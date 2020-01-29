// �쐬�� : ��
#include "game.hpp"
#include "job_scheduler.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"

#include "texture_manager.hpp"
#include "sprite_component.hpp"

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
