///
/// @file    interface.hpp
/// @author  ��
///          
/// @brief   �C���^�[�t�F�C�X���N���X
/// @details �O������delete����Ȃ��悤�A�f�X�g���N�^�̌Ăяo���𐧌����Ă��܂��B<br>
///          �e�h���N���X�̓f�X�g���N�^�ɏI���������������Ă��������B
///
#ifndef INCLUDED_EGEG_INTERFACE_HEADER_
#define INCLUDED_EGEG_INTERFACE_HEADER_
#include "egeg_common.hpp"
BEGIN_EGEG
class Interface
{
public :
    void addRef() { ++ref_cnt_; }
    void release()
    {
        if( --ref_cnt_ <= 0 )
        {
            delete this;
        }
    }

    unsigned getRefCount() const { return ref_cnt_; }

protected :
    virtual ~Interface() = 0 {}
private :
    unsigned ref_cnt_ = 1U;
};
END_EGEG
#endif /// !INCLUDED_EGEG_INTERFACE_HEADER_
/// EOF
