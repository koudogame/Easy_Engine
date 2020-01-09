///
/// @file    game.hpp
/// @author  板場
///          
/// @brief   ゲームクラス
/// @details ゲームの中核を内部で扱います。<br>
///          シングルトンクラスです。アクセスにはinstance関数を使用してください。
///
#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_
#include "easy_engine.hpp"
BEGIN_EG_EG
class Director;
class Game
{
public:
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

    Director* director_ = nullptr;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_GAME_HEADER_
/// EOF
