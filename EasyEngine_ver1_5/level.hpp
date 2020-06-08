///
/// @file   level.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include "task.hpp"
#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  Level
/// @brief  レベル
///
class Level
{
public :
    ///
    /// @brief  レベルファイルをロード
    ///
    /// @return true:成功　false:失敗
    ///
    bool load( const std::string& LevelFilePath );
    ///
    /// @brief  読み込んであるノードを解放
    ///
    void unload();

    ///
    /// @brief  ポーズ( 更新一時停止 )
    ///
    /// @details 描画は止まりません。 <br>
    ///          描画を止めたい場合、ベースシーンの描画コンポーネントの描画ステートを変更してください。
    ///
    void pause();
    ///
    /// @brief  ポーズ解除( 一時停止解除 )
    ///
    void unpause();

    ///
    /// @brief  タスクマネージャーを取得
    ///
    TaskManager* getTaskManager() noexcept { return &task_manager_; }

    ///
    /// @brief  ルートノードを取得
    ///
    LevelNode* getRootNode() const noexcept { return root_node_; }

private :
    Task task_update_;
    Task task_render_;
    TaskManager task_manager_;
    LevelNode* root_node_ = nullptr;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
