#ifndef INCLUDED_EG_EG_SCENE_HEADER_
#define INCLUDED_EG_EG_SCENE_HEADER_
// 作成者 : 板場
#include "easy_engine.hpp"

BEGIN_EG_EG
class SceneManager;

//
// シーン単位クラス
// 初期化に使用する値は各シーンにより異なることを想定して、初期化関数は定義していません。
// 各派生クラスは、各々初期化用の関数を定義して下さい。
//
class Scene
{
public :
    Scene( SceneManager* Manager ) :
        manager_( Manager )
    {}
    virtual ~Scene() = default;
    
    // 更新処理
    virtual void update() = 0;
    // 終了処理
    virtual void finalize() = 0;
    // 描画処理
    virtual void draw() = 0;

private :
    SceneManager* manager_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_HEADER_
// EOF
