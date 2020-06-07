///
/// @file   level_scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_SCENE_HEADER_
#define INCLUDED_EGEG_LEVEL_SCENE_HEADER_

#include "level_node.hpp"
#include "render_component.hpp"
#include "level_camera.hpp"
#include "level_light.hpp"

BEGIN_EGEG

///
/// @class  LevelScene
/// @brief  レベルノード「シーン」
///
/// @details 描画空間です。
///
class LevelScene :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kScene;
    NodeType getNodeType() const noexcept { return kNodeType; }

    ///
    /// @brief  描画コンポーネントを登録
    ///
    /// @param[in] Component : 描画モデル
    ///
    virtual void entry( RenderComponent* Component ) = 0;
    ///
    /// @brief  描画コンポーネントの登録を解除
    ///
    /// @param[in] Component : 登録を解除するモデル
    ///
    virtual void exit( RenderComponent* Component ) = 0;

    ///
    /// @brief  カメラをセット
    ///
    /// @param[in] Camera : カメラ
    ///
    virtual void setCamera( LevelCamera* Camera ) = 0;

    ///
    /// @brief  ライトを追加
    ///
    /// @param[in] Light : ライト
    ///
    virtual void addLight( LevelLight* ) = 0;

    ///
    /// @brief  描画
    ///
    /// @param[in] Delta : フレーム経過時間
    ///
    /// @details タスクマネージャーにジョブとして登録できるように、引数を指定しています。 <br>
    ///
    virtual void render( uint64_t Delta ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_SCENE_HEADER_
/// EOF
