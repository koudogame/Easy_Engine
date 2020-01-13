///
/// @file scene.hpp
/// @author 板場
///
/// @brief シーン基底クラス
///
///
#ifndef INCLUDED_EG_EG_SCENE_HEADER_
#define INCLUDED_EG_EG_SCENE_HEADER_
#include "easy_engine.hpp"
BEGIN_EGEG
class SceneManager;
class Scene
{
public :
    ///
    /// @brief コンストラクタ
    ///
    Scene( SceneManager* Manager ) :
        manager_( Manager )
    {}

    ///
    /// @brief デストラクタ
    ///
    virtual ~Scene() = default;

    ///
    /// @brief 更新処理
    ///
    virtual void update() = 0;

    ///
    /// @brief 終了処理
    ///
    virtual void finalize() = 0;

    ///
    /// @brief 描画処理
    ///
    virtual void draw() = 0;

protected :
    SceneManager* manager_; ///< @brief シーンマネージャー
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SCENE_HEADER_
/// EOF
