#ifndef INCLUDED_EG_EG_PLATFORM_HEADER_
#define INCLUDED_EG_EG_PLATFORM_HEADER_
// 作成者 : 板場
#include <functional>
#include "easy_engine.hpp"
#include "renderer.hpp"

BEGIN_EG_EG
//
// プラットフォームに依存する機能を提供するインターフェイス
//
// 初期化が行われていないインターフェイスが生成されることを防ぐため、
// インスタンス化を制限しています。
// 
// このインターフェイスはPlatformFactoryによって生成されます。
//
class IPlatform
{
public :
    virtual ~IPlatform() = default;

    //
    // 終了処理
    // 解放前に必要な処理を実装して下さい。
    //
    virtual void finalize() = 0;

    //
    // ゲームループ
    // 
    // in pUpdatefunc : 毎ループ呼び出す関数のポインタ。
    //
    // 引数の関数ポインタは、戻り値が bool 引数\がlong long型の関数へのポインタです。
    // 渡された関数の戻り値でfalse が返ってきた場合、ループを終了します。
    // 渡された関数の引数には、呼び出し毎の経過時間(: ミリ秒)を与えます。
    //
    virtual void gameLoop( std::function<bool(long long)> pUpdateFunc ) = 0;

    //
    // ダイアログボックスの表示
    //
    // in Message : 表示する文字列
    //
    virtual void showDialogBox( const char Message[] ) = 0;

protected :
    IPlatform() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_HEADER_
// EOF
