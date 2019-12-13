// 作成者 : 板場
// データの扱いが stackなのに対し、コンテナが vectorなのは、
// トラバースを可能にするため。


#include "scene_manager.hpp"
#include "scene.hpp"

BEGIN_EG_EG

// 関数の実装
/*===========================================================================*/
// 更新処理
void SceneManager::update()
{
    // 前回の更新で除外されたシーンを開放
    if( poped_scene_ )
    {
        poped_scene_->finalize();
        delete poped_scene_;
        poped_scene_ = nullptr;
    }

    for( auto& scene : scenes_ )
        scene->update();
}

// 描画処理
void SceneManager::draw()
{
    for( auto& scene : scenes_ )
        scene->draw();
}

// シーンの入れ替え処理
void SceneManager::swap( Scene *Next )
{
    pop();
    push( Next );
}

// シーンの除外処理
// すぐに開放すると、処理が残っている場合危険なので、
// 一旦、一時領域に逃す。
void SceneManager::pop()
{
    poped_scene_ = scenes_.back();
    scenes_.pop_back();
}

END_EG_EG
// EOF
