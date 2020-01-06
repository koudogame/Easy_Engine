#ifndef INCLUDED_EG_EG_DIRECTOR_HEADER_
#define INCLUDED_EG_EG_DIRECTOR_HEADER_
// 作成者 : 板場
#include "easy_engine.hpp"
#include "platform.hpp"
#include "renderer.hpp"

BEGIN_EG_EG
//
// 全体統括クラス
// シングルトンクラスです。アクセスには instance関数を使用して下さい。
//
class Director
{
public :
    ~Director();

    // インスタンスへのアドレスを取得します。
    static Director* instance() { static Director i; return &i; }
    // プラットフォームに依存する機能を提供するインターフェイスを取得します。
    IPlatform* getPlatform() const { return p_platform_; }
    // 描画機能を提供するインターフェイスを取得します。
    IRenderer* getRenderer() const { return p_renderer_; }

    //
    // 初期化処理
    // 必ず最初に呼び出して下さい。
    //
    // in Platform : プラットフォーム
    // in Renderer : レンダラー
    //
    // out true  : 初期化成功
    // out false : 初期化失敗
    //
    bool initialize( PlatformID Platform, RendererID Renderer );

    //
    // 終了処理
    // 必ず最後に呼び出して下さい。
    //
    void finalize();
private :
    Director();

    IPlatform* p_platform_;
    IRenderer* p_renderer_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_DIRECTOR_HEADER_
// EOF
