#ifndef INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
// 作成者 : 板場
#include <vector>
#include "easy_engine.hpp"

BEGIN_EG_EG
class Scene;

//
// シーン管理クラス
//
// シングルトンクラス。インスタンスへのアクセスは instance関数を使用してください。
// シーンの扱いは stack(後入れ先出し) です。 
// アクティブなシーンは最後に追加されたシーンを指します。
// update関数 及び draw関数 はリストに保存してある全てのシーンに対して関数の呼び出しを行います。
//
class SceneManager
{
public :
    // インスタンスへのアドレスを取得します。
    static SceneManager* instance() { static SceneManager i; return &i; }

    //
    // アクティブなシーンのupdate関数を呼び出します。
    //
    void update();
    //
    // アクティブなシーンのdraw関数を呼び出します。
    //
    void draw();

    //
    // アクティブなシーンを取得します。
    //
    inline Scene* getActive() const { return scenes_.back(); }
    //
    // シーンを追加します。
    // この時追加される位置は 一番最後です。
    // 
    // in Next : 追加するシーン
    //
    inline void push( Scene* Next ) { scenes_.push_back( Next ); }
    //
    // シーンを除外します。
    // この時除外の対象となるシーンは 最後に追加されたシーンです。
    //
    void pop();
    //
    // シーンを入れ替えます。
    // この時入れ替えの対象となるシーンは 最後に追加されたシーンです。
    //
    // in Next : 入れ替え後のシーン
    //
    void swap( Scene* Next );

private :
    std::vector<Scene*> scenes_;

    Scene* poped_scene_ = nullptr;
    SceneManager() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
// EOF
