// 作成者 : 板場
#include "scene_manager.hpp"
#include "system_manager.hpp"
#include "scene_factory.hpp"

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
    // シーンの生成＆初期化
    Scene* next = SceneFactory::instance()->create( ID );
    if( next == nullptr )
    {
        SystemManager::instance()->showDialogBox( 
            "シーンの生成に失敗しました。\n"
            "IDに対応するクリエイターがファクトリに登録されていません。\n"
            "\n場所 : SceneManager::push"
        );
        return;
    }

    if( next->initialize() == false )
    {
        SystemManager::instance()->showDialogBox( 
            "シーンの初期化に失敗しました。\n"
            "\n場所 : SceneManager::push"
        );
        return;
    }

    scenes_.push_back( next );
}

// シーンの削除
void SceneManager::pop()
{
    // 常にトップのシーンは保持しておく
    if( scenes_.size() <= 1U ) return;

    // シーンのポップ
    Scene* poped = scenes_.back();
    scenes_.pop_back();
    poped->finalize();
    delete poped;
}

// シーンの入れ替え
void SceneManager::swap( uint32_t ID )
{
    // シーンの生成＆初期化
    Scene* next = SceneFactory::instance()->create( ID );
    if( next == nullptr )
    {
        SystemManager::instance()->showDialogBox(
            "シーンの生成に失敗しました。\n"
            "IDに対応するクリエイターがファクトリに登録されていません。\n"
            "\n場所 : SceneManager::swap" 
        );
        return;
    }
    
    if( next->initialize() == false )
    {
        SystemManager::instance()->showDialogBox(
            "シーンの初期化に失敗しました。\n"
            "\n場所 : SceneManager::swap"
        );
        return;
    }

    // 現在アクティブなシーンを解放
    scenes_.back()->finalize();
    delete scenes_.back();

    // アクティブなシーンの入れ替え
    scenes_.pop_back();
    scenes_.push_back( next );
}

// 終了処理
void SceneManager::destroy()
{
    for (auto& scene : scenes_)
    {
        scene->finalize();
        delete scene;
    }
}
END_EGEG
// EOF
