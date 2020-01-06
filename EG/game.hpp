#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_
// 作成者 : 板場
#include "easy_engine.hpp"

BEGIN_EG_EG
class Director;
//
// ゲームクラス ≒　シーンの実行者
// ゲームの中核を内部で扱うクラスです。
// シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
//
class Game
{
public:
    static Game* instance() { static Game game; return &game; }

    //
    // ゲームの実行
    //
    void execute();

private:
    Game() = default;

    bool initialize();
    void finalize();
    bool update(long long Erapsed);

    Director* director_ = nullptr;
};
END_EG_EG
#endif // INCLUDED_EG_EG_GAME_HEADER_
// EOF
