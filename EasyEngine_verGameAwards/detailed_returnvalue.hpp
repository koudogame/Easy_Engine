///
/// @file   detailed_returnvalue.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_DETAILED_RETURNVALUE_HEADER_
#define INCLUDED_EGEG_DETAILED_RETURNVALUE_HEADER_
#include <string>
#include "egeg.hpp"
BEGIN_EGEG
/// 
/// @class    DetailedReturnValue
/// @brief    詳細情報を持つ戻り値
/// @detailed デバッグ時のみ、文字列を保持することができます。
///
template <class RetValType>
class DetailedReturnValue
{
public :
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
    operator RetValType() && noexcept { return std::move(value_); }
    RetValType* operator->() const noexcept { return &value_; }
    RetValType& get() noexcept { return value_; }

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
    template <class StringType>
    DetailedReturnValue( bool Condition, StringType&& ) :
        condition_( Condition )
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
#endif /// !INCLUDED_EGEG_DETAILED_RETURNVALUE_HEADER_
/// EOF
