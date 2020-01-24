///
/// @file    game.hpp
/// @author  板場
///          
/// @brief   ゲーム本体
/// @details ゲームのエントリークラスです。<br>
///          シングルトンクラスです。グローバルアクセスは提供しません。
///
#ifndef INCLUDED_EGEG_GAME_HEADER_
#define INCLUDED_EGEG_GAME_HEADER_
#include "easy_engine.hpp"
BEGIN_EGEG
class Game
{
public :
    ///
    /// @brief  初期化処理
    ///
    /// @return 初期化成功[ true ] 初期化失敗[ false ]
    ///
    bool initialize();
    ///
    /// @brief  終了処理
    ///
    void finalize();

    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 経過時間(: ミリ秒)
    ///
    void update( uint64_t DeltaTimeMS );
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_HEADER_
/// EOF
