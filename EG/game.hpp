#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_

// 作成者 : 板場

#include "easy_engine.hpp"

BEGIN_EG_EG

//
// ゲームクラス ≒　シーンの実行者
//
class Game
{
public:
    //
    // ゲームの実行
    //
    void execute();

private:
    bool initialize();
    void finalize();
    bool update(long long Erapsed);
};

END_EG_EG
#endif // INCLUDED_EG_EG_GAME_HEADER_
// EOF
