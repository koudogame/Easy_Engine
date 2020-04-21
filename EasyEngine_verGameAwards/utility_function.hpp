///
/// @file   utility_function.hpp
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
constexpr auto enumToValue( EnumClass Enumerator ) noexcept
{
    return static_cast<std::underlying_type_t<EnumClass>>(Enumerator);
}

///
/// @brief  オブジェクトを一意なIDに変換する
/// 
/// @tparam ValueType : 変換後のID型
///
/// @param[in] Object : 変換するオブジェクト
///
/// @return 引数のオブジェクトに対応した一意なID
///
template <class ValueType, class T>
ValueType uniqueid_cast( const T& Object ) noexcept
{
    return static_cast<ValueType>( reinterpret_cast<::std::uintptr_t>(&Object) );
}
///< nullptrは0
template <class ValueType>
ValueType uniqueid_cast( ::std::nullptr_t ) noexcept
{
    return static_cast<ValueType>(0);
}

END_EGEG
#endif /// !INCLUDED_EGEG_UTILITY_HEADER_
/// EOF
