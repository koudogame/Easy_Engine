///
/// @file   noncopyable.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_NONCOPYABLE_HEADER_
#define INCLUDED_EGEG_NONCOPYABLE_HEADER_
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   コピー禁止クラス
/// @brief   このクラスを基底に持つクラスに、コピー禁止属性を付加する
/// @details コピー - 禁止<br>
///          ムーブ - 可能
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
