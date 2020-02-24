///
/// @file   controller.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CONTROLLER_HEADER_
#define INCLUDED_EGEG_CONTROLLER_HEADER_
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Controller
/// @brief   �R���g���[���[���N���X
/// @details �e��f�o�C�X�ɑΉ������h���N���X�ŁA�L�[�ɑΉ�����������o�^���܂��B
///
class Controller
{
public :
    virtual ~Controller() = default;

    ///
    /// @brief   ���͏�Ԃ̍X�V
    /// @details �ێ����Ă�����̓f�o�C�X������͂��擾���A���͂ɑΉ��������������s���܂��B
    ///
    virtual void update() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_CONTROLLER_HEADER_
/// EOF
