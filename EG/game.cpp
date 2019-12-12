// 作成者 : 板場

#include "game.hpp"
#include "game_loop.hpp"


BEGIN_EG_EG

// 関数の実装
/*===========================================================================*/
// ゲームの実行処理
void Game::execute()
{
    // ゲームの初期化
    initialize();

    // ゲームループ
    GameLoop::loop( std::bind( &Game::update, this, std::placeholders::_1) );

    // ゲームの終了
    finalize();
}

// 初期化処理
//
// ゲームの初期化に必要な処理を記述する。
//
// 初期化に成功した場合は　true
// 初期化に失敗した場合は  false を戻り値として返却すること。
bool Game::initialize()
{


    return true;
}

// 終了処理
//
// ゲームの終了時に必要な処理を記述する
void Game::finalize()
{

}

// 更新処理
//
// 毎フレーム呼び出される。
// 引数として受け取る ErapsedMS は前回呼び出し時からの経過時間を格納している。
// 経過時間の単位はミリ秒(: ms)である。
//
// 更新を継続(ゲームを継続)する場合は　true
// 更新を終了(ゲームを終了)する場合は　false を戻り値として返却すること。
bool Game::update( long long ErapsedMS )
{
    return true;
}

END_EG_EG
// EOF
