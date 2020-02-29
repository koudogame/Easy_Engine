///
/// @file   application.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_APPLICATION_HEADER_
#define INCLUDED_EGEG_APPLICATION_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Application
/// @brief   �A�v���P�[�V�����G���g���[
///          
/// @details �V���O���g���N���X�ł��B�O���[�o���A�N�Z�X�͒񋟂��܂���B<br>
///
class Application final
{
public:
    inline Application() noexcept
    {
#ifdef _DEBUG
        static int create_cnt_;
        assert(!create_cnt_++ && "���ɐ�������Ă��܂��B");
#endif // !_DEBUG
    }

    ///
    /// @brief  �A�v���P�[�V�����̎��s
    ///
    void run();


    Application( const Application& ) = delete;
    Application& operator=( const Application& ) = delete;
private :
    bool initialize();
    void finalize();
    void mainloop();
};
END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_HEADER_
/// EOF
