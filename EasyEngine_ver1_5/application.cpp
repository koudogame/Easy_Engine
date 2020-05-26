// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "application.hpp"
#include <chrono>
#include <Windows.h>
#include "application_status.hpp"
#include "engine.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    using Ratio = std::ratio_divide<std::ratio<1,kFps<uintmax_t>>, std::micro>;
    constexpr long long kUsPerFrame = Ratio::num / Ratio::den;
}


/******************************************************************************

	Application

******************************************************************************/
 // 実行
void Application::operator()() const
{
    using namespace std::chrono;

    // エンジン初期化
    if( !EasyEngine::initialize() ) return;

    // メインループ
    auto last_time = high_resolution_clock::now();
    MSG msg{};
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
        { // メッセージ処理
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        { // アプリケーション更新処理
            auto now_time = high_resolution_clock::now();
            auto elapsed_time = now_time - last_time;
            if( duration_cast<microseconds>(elapsed_time).count() >= kUsPerFrame )
            { // 更新
                last_time = now_time;
                EasyEngine::getTaskManager()->execute( duration_cast<milliseconds>(elapsed_time).count() );
            }
        }
    }

    // エンジン終了
    EasyEngine::finalize();
}

END_EGEG
// EOF
