///
/// @file   application.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_APPLICATION_HEADER_
#define INCLUDED_EGEG_APPLICATION_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif // !_DEBUG
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Application
/// @brief   �A�v���P�[�V�����G���g���[
///          
/// @details �V���O���g���N���X�ł��B�O���[�o���A�N�Z�X�͒񋟂��܂���B<br>
///
class Application
{
public:
    inline Application()
    {
#ifdef _DEBUG
        static int create_cnt_;
        assert(!create_cnt_ && "���ɐ�������Ă��܂��B");
#endif // !_DEBUG
    }

    void run();

private:
    bool initialize();
    void finalize();
    void mainLoop();

    Application( const Application& ) = delete;
    Application& operator=( const Application& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_HEADER_
/// EOF
