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
    static float angle = 0.0F;

    sprite.setStatus(
        texture_,
        {640.0F, 350.0F},
        {0.0F, 0.0F, 32.0F, 32.0F},
        angle,
        {2.0F, 2.0F},
        { 16.0F, 16.0F },
        { 0.0F, 0.0F, 0.0F },
        1.0F,
        0.0F);

    angle += 1.0F;

    JobScheduler::instance()->execute( Delta );
    RenderingManager::instance()->beginRender( { 1.0F, 1.0F, 1.0F, 1.0F} );
    RenderBatch::instance()->render();
    RenderingManager::instance()->endRender();

    return true;
}
END_EGEG
// EOF
