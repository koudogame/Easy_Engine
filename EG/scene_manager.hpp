#ifndef INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SCENE_MANAGER_HEADER_

// 作成者 : 板場

#include <stack>
#include "easy_engine.hpp"

BEGIN_EG_EG

class Scene;

//
// シーン管理クラス
//
// シングルトンクラス。インスタンスへのアクセスは instance関数を使用する。
// シーンの扱いは stack(後入れ先出し) である。 
// アクティブなシーンは最後に追加されたシーン。
// update関数 及び draw関数 はリストに保存してある全てのシーンに対して関数の呼び出しを行う。
//
class SceneManager
{
public :
    // インスタンスへのアドレスを取得
    static SceneManager* instance() { static SceneManager i; return &i; }

    //
    // 保持しているシーンのupdate関数を呼び出す。
    //
    void update();
    //
    // 保持しているシーンのdraw関数を呼び出す。
    //
    void draw();

    //
    // アクティブなシーンを取得する
    //
    inline Scene* getActive() const { return scene_list_.back(); }
    //
    // シーンを追加する。
    // この時追加される位置は 一番最後
    // 
    // in Push : 追加するシーン
    //
    inline void push( Scene* Push ) { scene_list_.push_back( Push ); }
    //
    // シーンを除外する。
    // この時除外の対象となるシーンは 最後に追加されたシーン。
    //
    void pop();
    //
    // シーンを入れ替える。
    // この時入れ替えの対象となるシーンは 最後に追加されたシーン。
    //
    void swap( Scene* Swap );

private :
    std::stack<Scene*> scene_list_;

    Scene* poped_scene_ = nullptr;
    SceneManager() = default;
};

END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
// EOF
