///
/// @file   return_value.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RETURN_VALUE_HEADER_
#define INCLUDED_EGEG_RETURN_VALUE_HEADER_

#include <stdexcept>
#include <type_traits>
#include "egeg_def.hpp"

BEGIN_EGEG

struct Success{};
struct Failure{};
class reference_to_invalid_value
    : public std::logic_error
{
public :
    using Mybase = logic_error;
    explicit reference_to_invalid_value( const std::string& Message ) : Mybase( Message.c_str() ) {}
    explicit reference_to_invalid_value( const char* Message ) : Mybase( Message ) {}
};


///
/// @class   ReturnValue
/// @brief   ��Ԃ����߂�l
/// @details �������Ă����ꍇ�A���̃I�u�W�F�N�g��true�ɕϊ�����܂��B <br>
///           ���s���Ă����ꍇ�A���̃I�u�W�F�N�g��false�ɕϊ�����܂��B
///
/// @tparam ValueType : �߂�l�Ƃ��ĕێ�����I�u�W�F�N�g�̌^
///
template <class ValueType>
class ReturnValue
{
public :
    template <class ValType>
    ReturnValue( Success, ValType&& Value ) :
        condition_{ true },
        return_value_{ std::forward<ValType>(Value) }
    {}
    ReturnValue( Failure ) :
        condition_{ false },
        return_value_{}
    {}
    template <class ValType>
    ReturnValue( Failure, ValType&& InvalidValue ) :
        condition_{ false },
        return_value_{ std::forward<ValType>(InvalidValue) }
    {}
    
    operator bool() const noexcept { return condition_; }
    operator ValueType() && { if(!(*this)) throw reference_to_invalid_value{"�����Ȗ߂�l�ւ̃A�N�Z�X"}; return std::move(return_value_); }
    ValueType& operator*() { return get(); }
    ValueType& get() { if(!(*this)) throw reference_to_invalid_value{"�����Ȗ߂�l�ւ̃A�N�Z�X"}; return return_value_; }

private :
    bool condition_;
    ValueType return_value_;
};


///
/// @class   DetailedReturnValue
/// @brief   �ڍׂȏ�Ԃ����߂�l
/// @details �������Ă����ꍇ�A���̃I�u�W�F�N�g��true�ɕϊ�����܂��B <br>
///           ���s���Ă����ꍇ�A���̃I�u�W�F�N�g��false�ɕϊ�����܂��B
///
/// @tparam ValueType : ���ʂƂ��ĕێ�����I�u�W�F�N�g�^
///
template <class ValueType>
class DetailedReturnValue
{
public :
    template <class ValType>
    DetailedReturnValue( Success, ValType&& Value ) :
        condition_{ true },
        return_value_{ std::forward<ValType>(Value) }
    {}
    template <class StrType>
    DetailedReturnValue( Failure, StrType&& Message ) :
        condition_{ false },
        return_value_{},
        message_{ std::forward<StrType>(Message) }
    {}  
    template <class StrType, class ValType>
    DetailedReturnValue( Failure, StrType&& Message, ValType&& InvalidValue ) :
        condition_{ false },
        return_value_{ std::forward<ValType>(InvalidValue) },
        message_{ std::forward<StrType>(Message) }
    {}

    operator bool() const noexcept { return condition_; }
    operator ValueType() && { if(!(*this)) throw reference_to_invalid_value{ what() }; return std::move(return_value_); }
    ValueType& operator*() { return get(); }
    ValueType& get() { if(!(*this)) throw reference_to_invalid_value{ what() }; return return_value_; }
    const std::string& what() const noexcept { return message_; }

private :
    bool condition_;
    ValueType return_value_;
    std::string message_;
};
///< bool�p�������ꉻ
template<>
class DetailedReturnValue<bool>
{
public :
    DetailedReturnValue( Success ) noexcept :
        condition_{ true }
    {}
    template <class StrType>
    DetailedReturnValue( Failure, StrType&& Message ) :
        condition_{ false },
        message_{ Message }
    {}

    operator bool() const noexcept { return condition_; }
    bool operator*() { return get(); }
    bool get() { if(!(*this)) throw reference_to_invalid_value{what()}; return *this; }
    const std::string& what() const noexcept { return message_; }

private :
    bool condition_;
    std::string message_;
};


END_EGEG
#endif /// !INCLUDED_EGEG_RETURN_VALUE_HEADER_
/// EOF
