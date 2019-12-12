#ifndef INCLUDED_EG_EG_SCENE_HEADER_
#define INCLUDED_EG_EG_SCENE_HEADER_

// 作成者 : 板場

#include "easy_engine.hpp"

BEGIN_EG_EG

class SceneManager;
//
// シーン単位クラス
// 初期化に使用する値は各シーンにより異なるので、初期化関数は各シーンごとに用意する。
//
class Scene
{
public :
    Scene( SceneManager* Manager );
    virtual ~Scene() = default;
    
    // 更新処理
    void update();
    // 終了処理
    void finalize();
    // 描画処理
    void draw();

private :
    SceneManager* manager_;
};

END_EG_EG

#endif // INCLUDED_EG_EG_SCENE_HEADER_
// EOF
