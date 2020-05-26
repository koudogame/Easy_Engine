// �쐬�� : ��
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
 // ���s
void Application::operator()() const
{
    using namespace std::chrono;

    // �G���W��������
    if( !EasyEngine::initialize() ) return;

    // ���C�����[�v
    auto last_time = high_resolution_clock::now();
    MSG msg{};
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
        { // ���b�Z�[�W����
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        { // �A�v���P�[�V�����X�V����
            auto now_time = high_resolution_clock::now();
            auto elapsed_time = now_time - last_time;
            if( duration_cast<microseconds>(elapsed_time).count() >= kUsPerFrame )
            { // �X�V
                last_time = now_time;
                EasyEngine::getTaskManager()->execute( duration_cast<milliseconds>(elapsed_time).count() );
            }
        }
    }

    // �G���W���I��
    EasyEngine::finalize();
}

END_EGEG
// EOF
