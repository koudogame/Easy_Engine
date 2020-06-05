///
/// @file   id.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ID_HEADER_
#define INCLUDED_EGEG_ID_HEADER_

#include <cstdint>
#include <type_traits>
#include "egeg_def.hpp"
#include "raw_number.hpp"

BEGIN_EGEG

namespace impl
{
template <class ValueType, class T, class IsSigned>
ValueType uniqueid_impl( const T& Instance, IsSigned );
}


///
/// @brief  インスタンス毎に一意なIDを取得する
///
/// @tparam ValueType  : 取得するIDの型
///
template <class ValueType, class T>
ValueType uniqueid( const T& Instance )
{
    return impl::uniqueid_impl<ValueType>(Instance, std::is_signed<ValueType>{} );
}


///
/// @class  ConstantID
/// @brief  定数値ID
/// @details 数値型、もしくは列挙型以外のパラメータを受け取りません。
///
template <auto Value, class IsEnum=std::is_enum<decltype(Value)>, class=std::enable_if_t<std::is_arithmetic<decltype(Value)>::value || IsEnum::value>>
struct ConstantID
{
    operator typename RawNumber<Value>::NumTy() const noexcept
    {
        return RawNumber<Value>::value;
    }
    
    typename RawNumber<Value>::NumTy operator()() const noexcept
    {
        return RawNumber<Value>::value;
    }
};
///< 非列挙子用部分特殊化
template <auto Value>
struct ConstantID<Value, std::false_type>
{
    operator decltype(Value)() const noexcept
    {
        return Value;
    }

    decltype(Value) operator()() const noexcept
    {
        return Value;
    }
};


///
/// @class  TypeID
/// @brief  型毎に一意なID
///
/// @tparam NodeType      : IDを取得する型
/// @tparam ValueType : IDの型( デフォルトはstd::uintptr_t )
///
template <class Type, class ValueType=std::uintptr_t>
class TypeID
{
public :
    operator ValueType() const noexcept
    {
        return id_;
    }
    ValueType operator()() const noexcept
    {
        return id_;
    }
private :
    static const ValueType id_;
};
template <class Type, class ValueType>
const ValueType TypeID<Type, ValueType>::id_{ uniqueid<ValueType>(id_) };






namespace impl
{
template <class ValueType, class T, class IsSigned>
ValueType uniqueid_impl( const T& Instance, IsSigned )
{
    return static_cast<ValueType>(reinterpret_cast<std::intptr_t>(&Instance));
}
template <class ValueType, class T>
ValueType uniqueid_impl( const T& Instance, std::false_type )
{
    return static_cast<ValueType>(reinterpret_cast<std::uintptr_t>(&Instance));
}
}

END_EGEG
#endif /// !INCLUDED_EGEG_ID_HEADER_
/// EOF
