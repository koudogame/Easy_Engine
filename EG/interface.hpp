///
/// @file   interface.hpp
/// @author ��
///
/// @brief  �C���^�[�t�F�C�X���N���X 
///         �O������̊J���𐧌����Ă��܂��B<br>
///         release�֐��Ŏ��g�̊J���������L�q���Ă��������B
///
#ifndef INCLUDED_EG_EG_INTERFACE_HEADER_
#define INCLUDED_EG_EG_INTERFACE_HEADER_
#include "easy_engine.hpp"
BEGIN_EG_EG
class Interface
{
public :
    ///
    /// @brief  �Q�Ɛ��C���N�������g
    ///
    virtual void addRef() = 0;
    ///
    /// @brief   �J������
    /// @details �Q�Ɛ����f�N�������g���A�Q�Ǝ҂����Ȃ��Ȃ����Ƃ��ɊJ������܂��B
    ///
    virtual void release() = 0;

protected :
    virtual ~Interface() = default; ///< �O������̃f�X�g���N�^�Ăяo���𐧌����Ă��܂��B
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_INTERFACE_HEADER_
/// EOF
