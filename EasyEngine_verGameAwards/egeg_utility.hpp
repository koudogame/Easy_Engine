///
/// @file   egeg_utility.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_UTILITY_HEADER_
#define INCLUDED_EGEG_UTILITY_HEADER_
#include <type_traits>
#include <cstdint>
#include <string>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @brief  �z��̗v�f�����擾����
///
/// @param[in] : �v�f�����擾�������z��
///
/// @return �����̔z��̗v�f��
///
template <class Elem, size_t Size>
constexpr size_t getArraySize( const Elem (&)[Size] ) noexcept
{
    return Size;
}

///
/// @brief  enum class�̗v�f�����̊�{�^�ɕϊ�����
///
/// @param[in] Enumrator : �ϊ�����񋓎q
///
/// @return ��{�^�֕ϊ������l
///
template <class EnumClass>
constexpr auto EnumToValue( EnumClass Enumerator ) noexcept
{
    return static_cast<std::underlying_type_t<EnumClass>>(Enumerator);
}

///
/// @class   ���̃N���X�����Ɏ��N���X�ɁA�R�s�[�֎~������t������
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

/// 
/// @class    DetailedReturnValue
/// @brief    �ڍ׏������߂�l
/// @detailed �f�o�b�O���̂݁A�������ێ����邱�Ƃ��ł��܂��B
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
