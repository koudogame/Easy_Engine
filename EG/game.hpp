///
/// @file    game.hpp
/// @author  板場
///          
/// @brief   ゲームエントリークラス
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。
///
#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_
#include "easy_engine.hpp"
#include "platform.hpp"
BEGIN_EG_EG
class Game
{
public:
    ///< ターゲットプラットフォームです。
    static constexpr PlatformID kTargetPlatform = PlatformID::kWindows;

    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static Game* instance() { static Game game; return &game; }

    ///
    /// @brief  ゲームの実行
    ///
    void execute();

private:
    Game() = default;

    bool initialize();
    void finalize();
    bool update(long long Erapsed);
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_GAME_HEADER_
/// EOF
