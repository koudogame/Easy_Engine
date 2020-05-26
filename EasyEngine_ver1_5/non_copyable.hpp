///
/// @file   non_copyable.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_NON_COPYABLE_HEADER_
#define INCLUDED_EGEG_NON_COPYABLE_HEADER_

#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class  NonCopyable
/// @brief �R�s�[�֎~�N���X
///
/// @tparam Derived : ���̃N���X����h�����ꂽ�N���X�^
///
template <class Derived>
class NonCopyable
{
public :
    NonCopyable( const NonCopyable& ) = delete;
    NonCopyable& operator=( const NonCopyable& ) = delete;
    NonCopyable( NonCopyable&& ) = delete;
    NonCopyable& operator=( NonCopyable&& ) = delete;

protected :
    NonCopyable() noexcept = default;
    ~NonCopyable() = default;
};

END_EGEG
#endif /// !INCLUDED_EGEG_NON_COPYABLE_HEADER_
/// EOF
