///
/// @file   interface.hpp
/// @author ��
///
/// @brief  �C���^�[�t�F�C�X���N���X 
///         �O������̊J���𐧌����Ă��܂��B<br>
///         release�֐��Ŏ��g�̊J���������L�q���Ă���B<br>
///         �K�v�ȊJ�������� �f�X�g���N�^�Ɏ������Ă��������B
///
#ifndef INCLUDED_EG_EG_INTERFACE_HEADER_
#define INCLUDED_EG_EG_INTERFACE_HEADER_
#include "easy_engine.hpp"
BEGIN_EG_EG
class Interface
{
public :
    Interface() : ref_cnt_( 1U ) {}

    ///
    /// @brief  �Q�ƏW���擾���܂��B
    ///
    /// @return �Q�Ɛ�
    ///
    unsigned getReferencedNum() const { return ref_cnt_; }

    ///
    /// @brief  �Q�Ɛ��C���N�������g
    ///
    void addRef() { ++ref_cnt_; }
    ///
    /// @brief   �J������
    /// @details �Q�Ɛ����f�N�������g���A�Q�Ǝ҂����Ȃ��Ȃ����Ƃ��ɊJ������܂��B
    ///
    void release()
    {
        if( --ref_cnt_ <= 0U )
        {
            delete this;
        }
    }

protected :
    virtual ~Interface() = default; ///< �O������̃f�X�g���N�^�Ăяo���𐧌����Ă��܂��B
private :
    unsigned ref_cnt_;  /// �Q�Ɛ�
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_INTERFACE_HEADER_
/// EOF
