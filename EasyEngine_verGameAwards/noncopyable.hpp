///
/// @file   noncopyable.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_NONCOPYABLE_HEADER_
#define INCLUDED_EGEG_NONCOPYABLE_HEADER_
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   �R�s�[�֎~�N���X
/// @brief   ���̃N���X�����Ɏ��N���X�ɁA�R�s�[�֎~������t������
/// @details �R�s�[ - �֎~<br>
///          ���[�u - �\
///
template <class Derived>
class NonCopyable
{
public :
    NonCopyable( const NonCopyable& ) = delete;
    NonCopyable& operator=( const NonCopyable& ) = delete;
    NonCopyable( NonCopyable&& ) noexcept = default;
    NonCopyable& operator=( NonCopyable&& ) noexcept = default;

protected :
    NonCopyable() noexcept = default;
    ~NonCopyable() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_NONCOPYABLE_HEADER_
/// EOF
