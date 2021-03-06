// 作成者 : 板場
#include "entry_scene.hpp"
#include "uid.hpp"
#include "timer.hpp"
#include "scene_factory.hpp"
#include "scene_manager.hpp"
#include "job_scheduler.hpp"

REGISTER_SCENE( EGEG TypeID<EGEG EntryScene>::getID(), []()->EGEG Scene*{ return new EGEG EntryScene; } )

BEGIN_EGEG
// EntryScene : 関数の実装
/*===========================================================================*/
// 初期化
bool EntryScene::initialize()
{
    job_.setFunction( this, &EntryScene::update );
    JobScheduler::instance()->registerJob( 0, &job_ );

    return true;
}
// 終了
void EntryScene::finalize()
{
    JobScheduler::instance()->unregisterJob( &job_ );
}

// 更新処理
void EntryScene::update( uint64_t DeltaMS )
{
    static uint64_t Erapsed;

    Erapsed += DeltaMS;
    if( Erapsed >= 1000ULL )
        SceneManager::instance()->swap( 0U );
}
END_EGEG
// EOF
