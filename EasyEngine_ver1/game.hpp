///
/// @file    game.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_GAME_HEADER_
#define INCLUDED_EGEG_GAME_HEADER_
#include "easy_engine.hpp"
#include "sprite_component.hpp"
BEGIN_EGEG
class ITexture;
///
/// @class  Game
///          
/// @brief   ゲーム本体
/// @details ゲームのエントリークラスです。<br>
///          シングルトンクラスです。グローバルアクセスは提供しません。
///
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
    /// @return 更新継続[ true ]　更新終了[ false ]
    ///
    bool update( uint64_t DeltaTimeMS );

private :
    SpriteComponent sprite;
    ITexture *texture_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_HEADER_
/// EOF
