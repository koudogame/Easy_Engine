///
/// @file   result.hpp
/// @author 板場
/// @brief  関数の戻り値用ライブラリ
///
#ifndef INCLUDED_EGEG_RESULT_HEADER_
#define INCLUDED_EGEG_RESULT_HEADER_

#include <type_traits>
#include <stdexcept>
#include "egeg.hpp"

BEGIN_EGEG

struct Success {};
struct Failure {};
class reference_to_invalid_value
    : public ::std::logic_error
{
public :
    using Mybase = logic_error;
    explicit reference_to_invalid_value( const std::string& Message ) : Mybase( Message.c_str() ) {}
    explicit reference_to_invalid_value( const char* Message ) : Mybase( Message ) {}
};

///
/// @class  Result
/// @brief  状態を持つ結果
///
/// @tparam ValueType : 結果として持つ値型
///
template <class ValueType>
class Result 
{
public :
    template <class ValType>
    Result( Success, ValType&& Value ) :
        condition_( true ),
        value_( std::forward<ValType>(Value) )
    {
    }

    Result( Failure ) :
        condition_( false )
    {
    }
    ///< デフォルトコンストラクタを持たないクラス用
    template <class ValType>
    Result( Failure, ValType&& InvalidValue ) :
        condition_( false ),
        value_( InvalidValue )
    {
    }

    operator bool() const noexcept { return condition_; }
    operator ValueType() && { if(!(*this)) throw reference_to_invalid_value{"無効な戻り値へのアクセス"}; return std::move(value_); }
    ValueType& operator*() { return get(); }
    ValueType& get() { if(!(*this)) throw reference_to_invalid_value{"無効な戻り値へのアクセス"}; return value_; }

private :
    bool condition_;
    ValueType value_;
};
template <>
class Result<bool>
{
public :
    Result( bool Value ) noexcept :
        condition_( Value )
    {
    }
    Result( Success ) noexcept :
        condition_( true )
    {
    }
    Result( Failure ) noexcept :
        condition_( false )
    {
    }

    operator bool() const noexcept { return condition_; }
    bool operator*() const noexcept { return get(); }
    bool get() const noexcept { return *this; }

private :
    bool condition_;
};

///
/// @class  DetailedResult
/// @brief  詳細な結果
///
/// @tparam ValueType : 結果として持つ値型
///
template <class ValueType>
class DetailedResult
{
public :
    template <class ValType>
    DetailedResult( Success, ValType&& Value ) :
        condition_( true ),
        value_( std::forward<ValType>(Value) )
    {
    }

    template <class StrType>
    DetailedResult( Failure, StrType&& Message ) :
        condition_( false ),
        message_( std::forward<StrType>(Message) )
    {
    }
    ///< デフォルトコンストラクタを持たないクラス用
    template <class StrType, class ValType>
    DetailedResult( Failure, StrType&& Message, ValType&& InvalidValue ) :
        condition_( false ),
        message_( std::forward<StrType>(Message) ),
        value_( std::forward<ValType>(InvalidValue) )
    {
    }

    operator bool() const noexcept { return condition_; }
    operator ValueType() && { if(!(*this)) throw reference_to_invalid_value{what()}; return std::move(value_); }
    ValueType& operator*() { return get(); }
    ValueType& get() { if(!(*this)) throw reference_to_invalid_value{what()}; return value_; }
    const std::string& what() const noexcept { return message_; }

private :
    bool condition_;
    ValueType value_;
    std::string message_;
};
template <>
class DetailedResult<bool>
{
public :
    DetailedResult( Success ) noexcept :
        condition_( true )
    {
    }

    template <class StrType>
    DetailedResult( Failure, StrType&& Message ) :
        condition_( false ),
        message_( std::forward<StrType>(Message) )
    {
    }

    operator bool() const noexcept { return condition_; }
    bool operator*() { return get(); }
    bool get() { if(!(*this)) throw reference_to_invalid_value{what()}; return *this; }
    const std::string& what() const noexcept { return message_; }

private :
    bool condition_;
    std::string message_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RESULT_HEADER_
/// EOF
