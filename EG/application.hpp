#ifndef INCLUDED_EG_EG_APPLICATION_HEADER_
#define INCLUDED_EG_EG_APPLICATION_HEADER_

// 作成者 : 板場

#include <memory>
#include "easy_engine.hpp"

BEGIN_EG_EG

//
// アプリケーションクラス
//
// シングルトンクラス。アクセスには instance関数を使用する。
// ゲームの実行に際して、プラットフォーム毎に異なる仕様を吸収する。
// 静的なアクセスを提供する。
// インスタンス化を禁止している。
//
class Application
{
public :
    //
    // インスタンスへのアドレスを取得
    //
    static Application* instance();

    //
    // 実行
    //
    void execute();

private :
    Application();
    class Impl;
    std::unique_ptr<Impl> p_impl_;
};

END_EG_EG
#endif // INCLUDED_EG_EG_APPLICATION_HEADER_
// EOF
