///
/// @file   egeg_utility.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_UTILITY_HEADER_
#define INCLUDED_EGEG_UTILITY_HEADER_
#include <type_traits>
#include <cstdint>
#include <string>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @brief  配列の要素数を取得する
///
/// @param[in] : 要素数を取得したい配列
///
/// @return 引数の配列の要素数
///
template <class Elem, size_t Size>
constexpr size_t getArraySize( const Elem (&)[Size] ) noexcept
{
    return Size;
}

///
/// @brief  enum classの要素をその基本型に変換する
///
/// @param[in] Enumrator : 変換する列挙子
///
/// @return 基本型へ変換した値
///
template <class EnumClass>
constexpr auto EnumToValue( EnumClass Enumerator ) noexcept
{
    return static_cast<std::underlying_type_t<EnumClass>>(Enumerator);
}

///
/// @class   このクラスを基底に持つクラスに、コピー禁止属性を付加する
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

/// 
/// @class    DetailedReturnValue
/// @brief    詳細情報を持つ戻り値
/// @detailed デバッグ時のみ、文字列を保持することができます。
///
template <class RetValType>
class DetailedReturnValue
{
public :
    using ValueType = RetValType;
#ifdef _DEBUG
    template <class ValueType>
    DetailedReturnValue( bool Condition, ValueType&& Value ) :
        condition_( Condition ),
        value_( std::forward<ValueType>(Value) ),
        status_( "No status" )
    {}
    template <class ValueType, class StringType>
    DetailedReturnValue( bool Condition, ValueType&& Value, StringType&& Status ) :
        condition_( Condition ),
        value_( std::forward<ValueType>(Value) ),
        status_( std::forward<StringType>(Status) )
    {}
#else
    template <class ValueType>
    DetailedReturnValue( bool Condition, ValueType&& Value ) :
        condition_( Condition ),
        value_( std::forward<ValueType>(Value) ) {}
    template <class ValueType, class StringType>
    DetailedReturnValue( bool Condition, ValueType&& Value, StringType&& ) :
        condition_( Condition ),
        value_( std::forward<ValueType>(Value) ) {}
#endif
    operator bool() const noexcept { return condition_; }
    operator RetValType() &  noexcept { return value_; }
    operator RetValType() && noexcept { return std::move(value_); }
    RetValType& get() const noexcept { return value_; }

private :
    bool condition_;
    RetValType value_;

#ifdef _DEBUG
    ::std::string status_;
#endif
};
template <>
class DetailedReturnValue<bool>
{
public: 
#ifdef _DEBUG
    DetailedReturnValue( bool Condition ) :
        condition_( Condition ),
        status_( "No status" )
    {}
    template <class StringType>
    DetailedReturnValue( bool Condition, StringType&& Status ) :
        condition_( Condition ),
        status_( std::forward<StringType>(Status) )
    {}
#else
    DetailedReturnValue( bool Condition ) :
        condition_( Condition )
    {}
    DetailedReturnValue( bool Condition, StringType&& ) :
        condition_( Condition ),
    {}
#endif
    operator bool() const noexcept { return condition_; }

private :
    bool condition_;
#ifdef _DEBUG
    ::std::string status_;
#endif
};
END_EGEG
#endif /// !INCLUDED_EGEG_UTILITY_HEADER_
/// EOF
