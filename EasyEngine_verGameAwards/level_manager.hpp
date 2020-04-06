///
/// @file   level_manager.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#include <memory>
#include <vector>
#include "factory.hpp"  /// レベルはファクトリによって生成する。
#include "uid.hpp"      /// レベルのIDはUIDにより生成する。

///
/// @def    REGISTER_LEVEL
/// @brief  レベルの登録
///
/// @param[in] LevelType : 登録するレベル型
///
#define REGISTER_LEVEL( LevelType ) \
REGISTER_WITH_FACTORY( LevelFactory, LevelType, LevelID<LevelType> )

BEGIN_EGEG

class Level;                                               ///< Levelクラス前方宣言( 循環参照回避 )
template class Factory<Level, class LevelManager*>;        ///< レベル用ファクトリクラスの明示的インスタンス化
using LevelFactory = Factory<Level, class LevelManager*>;  ///< レベル用ファクトリクラス型
template <class LevelType> using LevelID = UID<LevelType>; ///< レベル用ID

///
/// @class   LevelManager
/// @brief   レベルマネージャー
///
/// @details 「現在のレベル」「アクティブなレベル」は一番最後に遷移したレベルのことを指します。<br>
///          レベルの遷移に関して、現在のレベルからのリクエストであることが前提です。
///
class LevelManager
{
public :

    ///
    /// @brief   レベルの遷移
    /// @details 現在保持している全レベルを破棄し、新しいレベルを生成します。<br>
    ///           履歴にあるレベルへの遷移の場合、履歴をそこまで戻します。<br>
    ///           履歴にないレベルへの遷移の場合、履歴に新しいレベルを追加します。
    ///
    /// @tparam NewLevelType : 遷移先レベル型
    ///
    template <class NewLevelType>
    void transition()
    {
        transition( LevelID<NewLevelType>() );
    }

    ///
    /// @brief   レベルの遷移
    /// @details 現在のレベルは破棄せず、新しいレベルを生成します。<br>
    ///          履歴の変更はありません。
    ///
    /// @tparam NewLevelType : 遷移先レベル型
    ///
    template <class NewLevelType>
    void push()
    {
        push( LevelID<NewLevelType>() );
    }

    ///
    /// @brief   レベルの遷移
    /// @details 現在のレベルを破棄し、新しいレベルを生成します。<br>
    ///          遷移履歴の最後の要素を、新しいレベルのIDで上書きします。
    ///
    /// @tparam NewLevelType : 遷移先レベル型
    ///
    template <class NewLevelType>
    void swap()
    {
        swap( LevelID<NewLevelType>() );
    }

    ///
    /// @brief   レベルの遷移 
    /// @details 現在のレベルを破棄した後、遷移履歴を参照し一つ前のレベルへ遷移します。<br>
    ///          遷移先のレベルがない場合、遷移を行いません。<br>
    ///          遷移先のレベルに関して、インスタンスが残っている場合新しくレベルの生成は行いません。
    ///
    void back();

private :
    ///< 初期化済みのレベルを返却( 無効な場合nullptr )
    std::unique_ptr<Level> createLevel( uint32_t LevelID );

    void transition( uint32_t );
    void push( uint32_t );
    void swap( uint32_t );


    std::vector<std::unique_ptr<Level>> level_list_;
    size_t path_idx_ = 0U;
    std::vector<uint32_t> transition_path_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
