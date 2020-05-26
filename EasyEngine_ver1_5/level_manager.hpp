///
/// @file   level_manager.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_

#include <memory>
#include <string>
#include "non_copyable.hpp"
#include "task.hpp"

BEGIN_EGEG

class Level;    ///< Level前方宣言( 循環参照回避 )

///
/// @class LevelManager
/// @brief レベルマネージャー
///
class LevelManager final :
    NonCopyable<LevelManager>
{
public :
    static std::unique_ptr<LevelManager> create();
    ~LevelManager();

    ///
    /// @brief   レベルの遷移
    ///
    /// @param[in] LevelFilePath : 読み込むレベル構成ファイルのパス
    ///
    /// @details 現在保持している全レベルを破棄し、新しいレベルを生成します。 <br>
    ///           履歴にあるレベルへの遷移の場合、履歴をそこまで戻します。 <br>
    ///           履歴にないレベルへの遷移の場合、履歴に新しいレベルを追加します。
    ///
    void transition( std::string LevelFilePath );

    ///
    /// @brief   レベルの追加
    ///
    /// @param[in] LevelFilePath : 読み込むレベル構成ファイルのパス
    ///
    /// @details 現在のレベルを破棄せず、新しいレベルを追加します。 <br>
    ///           遷移履歴の変更はありません。
    ///
    void push( const std::string& LevelFilePath );

    ///
    /// @brief   現在のレベルを入れ替える
    ///
    /// @paramp[in] LevelFilePath : 読み込むレベル構成ファイルのパス
    ///
    /// @details 現在のレベルを破棄し、新しいレベルと入れ替えます。 <br>
    ///           遷移履歴の最後の要素を新しいレベルで上書きします。
    ///
    void swap( std::string LevelFilePath );

    ///
    /// @brief   1つ前のレベルへ戻る
    ///
    /// @details 現在のレベルを破棄した後、遷移履歴を参照して1つ前のレベルへ遷移します。 <br>
    ///           1つ前のレベルがない場合、遷移は行われません。 <br>
    ///           1つ前のレベルについて、push()による遷移の後でインスタンスが残っている場合は新しくレベルの生成を行いません。
    ///
    void back();



    void destructionFinalizedLevel( uint64_t );
private :
    LevelManager() noexcept;
    std::unique_ptr<Level> createLevel( const std::string& );

    Task task_;
    std::vector<std::unique_ptr<Level>> levels_;
    size_t path_index_ = 0U;
    std::vector<std::string> transition_path_;
    std::vector<std::unique_ptr<Level>> finalized_levels_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
