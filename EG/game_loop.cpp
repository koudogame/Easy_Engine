// �쐬�� : ��

#include "game_loop.hpp"
#include <Windows.h>
#include <chrono>


// unnamed namespace
/*===========================================================================*/
namespace
{

    constexpr long long kFramePerUS = 16666LL;  // �t���[�����̎���(: �}�C�N���b)

} // unnamed namespace


BEGIN_EG_EG

// �֐��̎���
/*===========================================================================*/
// �Q�[�����[�v
void GameLoop::loop( std::function<bool(long long)> pFunc )
{
    using namespace std::chrono;


    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;

    MSG msg = {};
    while( msg.message != WM_QUIT )
    {
        // ���b�Z�[�W����
        if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // �Q�[������
        else
        {
            // �t���[�����[�g����
            curr_time = high_resolution_clock::now();
            auto erapsed_time = curr_time - last_time;
            if( duration_cast<microseconds>(erapsed_time).count() >= kFramePerUS )
            {
                last_time = curr_time;

                if( !pFunc(duration_cast<milliseconds>(erapsed_time).count()) )
                    break;
#ifdef _DEBUG
                long long erapsed_ms = duration_cast<microseconds>(erapsed_time).count();
                int fps = (int)(1.0F / ((float)(erapsed_ms) / 1000000.0F));
                char c_fps[256];
                wsprintf( c_fps, TEXT("FPS : %d"), fps );
                SetWindowText( FindWindow("Game_MainWindow", nullptr), c_fps );
#endif
            }
        }
    }
}

END_EG_EG
// EOF
