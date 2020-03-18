///
/// @file   level_manager.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#include <memory>
#include <vector>
#include "factory.hpp"
BEGIN_EGEG
class Level;    ///< Levelクラス前方前言( 循環参照回避 )
using LevelFactory = Factory<Level>;

///
/// @class  LevelManager
/// @brief  レベルマネージャー
///
class LevelManager
{
public :

    ///
    /// @brief   レベルの遷移
    /// @details 現在のレベルを破棄し、遷移の履歴を保持します。
    ///
    /// @tparam NewLevel : 遷移先レベル型
    ///
    template <class NewLevel>
    void transition()
    {

    }

    ///
    /// @brief   レベルの遷移
    /// @details 現在のレベルは破棄せず、遷移の履歴を保持します。
    ///
    /// @tparam NewLevel : 遷移先レベル型
    ///
    template <class NewLevel>
    void push();

    ///
    /// @brief   レベルの遷移
    /// @details 現在のレベルを破棄し、繊維の履歴を保持しません。
    ///
    /// @tparam NewLevel : 遷移先レベル型
    ///
    template <class NewLevel>
    void swap();

    ///
    /// @brief   レベルの遷移
    /// @details 履歴を参照し、一つ前のレベルへ遷移します。<br>
    ///          遷移先のレベルがない場合、繊維を行いません。<br>
    ///          遷移先のレベルに関して、インスタンスが残っている場合新しくレベルの生成は行いません。
    ///
    void back();

private :
    std::vector<std::unique_ptr<Level>> level_list_;
    std::vector<uint32_t> transition_path_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
