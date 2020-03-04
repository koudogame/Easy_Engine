///
/// @file   controller.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CONTROLLER_HEADER_
#define INCLUDED_EGEG_CONTROLLER_HEADER_
#include "egeg_utility.hpp"
#include "input_device.hpp"
BEGIN_EGEG
///
/// @class   Controller
/// @brief   �R���g���[���[���N���X
/// @details �e��f�o�C�X�ɑΉ������h���N���X�ŁA�L�[�ɑΉ�����������o�^���܂��B<br>
///          �����̃R���g���[���|�����̃I�u�W�F�N�g�����삳��邱�Ƃ�h�����߂ɁA�R�s�[���֎~���Ă��܂��B
///
class Controller : 
    NonCopyable<Controller>
{
public :
    /// ���ꃁ���o�֐�
    Controller()                          = default;
    virtual ~Controller()                 = default;
    Controller( Controller&& )            = default;
    Controller& operator=( Controller&& ) = default;

    ///
    /// @brief   ���͏�Ԃ̍X�V
    /// @details �ێ����Ă�����̓f�o�C�X������͂��擾���A���͂ɑΉ��������������s���܂��B
    ///
    virtual void update() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_CONTROLLER_HEADER_
/// EOF
