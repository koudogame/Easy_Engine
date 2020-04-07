// �쐬�� : ��
#include "game.hpp"
#include "job_scheduler.hpp"
#include "scene_manager.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"
#include "uid.hpp"
#include "entry_scene.hpp"

BEGIN_EGEG
// Game : �֐��̎���
/*===========================================================================*/
// ����������
bool Game::initialize()
{
    SceneManager::instance()->push( TypeID<EntryScene>::getID() );
    return true;
}

// �I������
void Game::finalize()
{
    SceneManager::instance()->destroy();
}

// �X�V����
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
