///
/// @file   level.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include "task.hpp"
#include "level_empty.hpp"

BEGIN_EGEG

///
/// @class  Level
/// @brief  レベル
///
/// @detailes  レベルはツリー構造のレベルノードにより構成されます。           <br>
///                                                                    <br>
///            ルートノードの直接の子に当たる集合に、ベースシーンは位置します。 <br>
///            ベースシーンは必ず、他のシーンよりも先に配置して下さい。        <br>
///            この要件により、ベースシーンへのアクセスを一意なものにできます。 <br>
///            ベースシーンへアクセス )                                   <br>
///             Level level;                                           <br>
///                 ...levelを初期化...                                 <br>
///             LevelNode* root_node = level->getRootNode();           <br>
///             LevelScene* base_scene = root_node->getChild<LevelScene>( 0 );
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
    /// @brief  レベルをアンロード
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
    LevelNode* getRootNode() const noexcept { return root_node_.get(); }

private :
    bool loadNodes( std::istream& );
    std::unique_ptr<LevelNode> loadNode( std::string&, std::istream& );

    Task task_update_;
    Task task_render_;
    TaskManager task_manager_;
    std::unique_ptr<LevelNode> root_node_ = nullptr;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
