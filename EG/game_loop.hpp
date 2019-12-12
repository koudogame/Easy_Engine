#ifndef INCLUDED_EG_EG_GAME_LOOP_HEADER_
#define INCLUDED_EG_EG_GAME_LOOP_HEADER_

// 作成者 : 板場

#include <functional>
#include "easy_engine.hpp"

BEGIN_EG_EG

//
// ゲームループクラス
//
// ゲームループに際して、プラットフォーム毎に異なる仕様を吸収する。
// 静的なアクセスを提供する。
// インスタンスの生成は禁止している。
//
class GameLoop
{
public :
    //
    // ゲームループ
    // 
    // in pFunction : 毎ループ呼び出す関数のポインタ。
    //
    // 引数の関数ポインタは、戻り値が bool 引数がlong long型の関数。
    // 渡された関数の戻り値でfalse が返ってきた場合、ループを終了する。
    // 渡された関数の引数には、呼び出し毎の経過時間(: ミリ秒)を与える。
    //
    static void loop( std::function<bool(long long)> pFunction );

private :
    GameLoop() = default;
};

END_EG_EG
#endif // INCLUDED_EG_EG_GAME_LOOP_HEADER_
// EOF
