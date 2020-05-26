///
/// @file   application.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_APPLICATION_HEADER_
#define INCLUDED_EGEG_APPLICATION_HEADER_

#ifdef _DEBUG
#include <cassert>
#endif
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class Application
/// @brief �A�v���P�[�V�����C���X�^���X
///
/// @details �V���O���g���N���X�ł��B�O���[�o���A�N�Z�X�͒񋟂��܂���B
///
class Application final
{
public :
    Application() noexcept
    {
#ifdef _DEBUG
    static int create_cnt_;
    assert( !create_cnt_++ && "�A�v���P�[�V�����C���X�^���X�𕡐��������邱�Ƃ͂ł��܂���B" );
#endif
    }
    void operator()() const;
};

END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_HEADER_
/// EOF
