///
/// @file   controller.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_CONTROLLER_HEADER_
#define INCLUDED_EGEG_CONTROLLER_HEADER_

#include "non_copyable.hpp"

BEGIN_EGEG

///
/// @class   Controller
/// @brief   �R���g���[���[
/// @details �e��f�o�C�X�ɑΉ������h���N���X�ŁA���͂ɑΉ�����������o�^���܂��B <br>
///           �Ӑ}���������̃R���g���[���[����P�̃I�u�W�F�N�g�����삳��邱�Ƃ�h�����߁A�R�s�[���֎~���Ă��܂��B
///
class Controller :
    NonCopyable<Controller>
{
public :
    Controller() = default;
    virtual ~Controller() = default;
    Controller( const Controller& ) = delete;
    Controller& operator=( const Controller& ) = delete;
    Controller( Controller&& ) = default;
    Controller& operator=( Controller&& ) = default;

    ///
    /// @brief   �X�V
    /// @details ���̓f�o�C�X����̓��͂ɑΉ��������������s���܂��B
    ///
    virtual void update() = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CONTROLLER_HEADER_
/// EOF
