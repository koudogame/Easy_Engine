// 作成者 : 板場
#include "scene_manager.hpp"
#include "system_manager.hpp"
#include "uid.hpp"

BEGIN_EGEG
// SceneManager : 関数の実装
/*===========================================================================*/
// コンストラクタ
SceneManager::SceneManager()
{

}
// デストラクタ
SceneManager::~SceneManager()
{

}

// シーンの追加
void SceneManager::push( uint32_t ID )
{
   /* Scene* next = 
        dynamic_cast<Scene*>(GameObjectFactory::instance()->create( ID ));
    if( next == nullptr )
    {
        SystemManager::instance()->showDialogBox( 
            "シーンの生成に失敗しました。\n"
            "IDがシーンのものでないか、シーンがファクトリに登録されていません。"
        );
        return;
    }

    if( next->initialize() == false )
    {
        SystemManager::instance()->showDialogBox( "シーンの初期化に失敗しました。" );
        return;
    }
    next->setActive( true );

    scenes_.back()->setActive( false );
    scenes_.push_back( next );*/
}

// シーンの削除
void SceneManager::pop()
{
    // 常にトップのシーンは保持しておく
    if( scenes_.size() <= 1U ) return;

    // シーンのポップ
    Scene* poped = scenes_.back();
    scenes_.pop_back();
    //poped->finalize();
    delete poped;
}

// シーンの入れ替え
void SceneManager::swap( uint32_t ID )
{
    pop();
    push( ID );
}
END_EGEG
// EOF
