///
/// @file    shared_object.hpp
/// @author  ��
///          
/// @brief   ���L�I�u�W�F�N�g
/// @details �O������delete����Ȃ��悤�A�f�X�g���N�^�̌Ăяo���𐧌����Ă��܂��B<br>
///          �e�h���N���X�̓f�X�g���N�^�ɏI���������������Ă��������B
///
#ifndef INCLUDED_EGEG_SHARED_OBJECT_HEADER_
#define INCLUDED_EGEG_SHARED_OBJECT_HEADER_
#include "egeg_common.hpp"
BEGIN_EGEG
class SharedObject
{
public :
    SharedObject() = default;
    SharedObject( const SharedObject& ) { addRef(); }
    SharedObject& operator=( const SharedObject& ) { addRef(); }

    void addRef() { ++ref_cnt_; }
    unsigned release()
    {
        unsigned after_ref_cnt = --ref_cnt_;

        if( after_ref_cnt <= 0 )
        {
            delete this;
        }
        return after_ref_cnt;
    }

    unsigned getRefCount() const { return ref_cnt_; }

protected :
    virtual ~SharedObject() = 0 {}
private :
    unsigned ref_cnt_ = 1U;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHARED_OBJECT_HEADER_
/// EOF
