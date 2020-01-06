// 作成者 : 板場
#include "scene_manager.hpp"
#include "scene.hpp"
#include <shcore.h>

BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// アクティブなシーンの更新処理
void SceneManager::update()
{
    // 前回のフレームで除外されたシーンを解放する
    if( poped_scene_ )
    {
        poped_scene_->finalize();
        delete poped_scene_;
        poped_scene_ = nullptr;
    }


    getActive()->update();
}

// アクティブなシーンの描画処理
void SceneManager::draw()
{
    getActive()->draw();
}

// シーンの除外処理
// 除外後、即座にシーンを解放すると処理が残っている場合に危険なので、
// 除外対象のシーンを一時領域に格納しておく。
void SceneManager::pop()
{
    poped_scene_ = scenes_.back();
    scenes_.pop_back();
}

// シーンの入れ替え処理
void SceneManager::swap( Scene* Next )
{
    pop();
    push( Next );
}
END_EG_EG
// EOF
