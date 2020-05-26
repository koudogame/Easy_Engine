///
/// @file   raw_number.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_RAW_NUMBER_HEADER_
#define INCLUDED_EGEG_RAW_NUMBER_HEADER_

#include <type_traits>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class   RawNumber
/// @brief   列挙子をその基底型に変換
/// @details 列挙子以外のパラメータは受け取りません。
///
/// @tparam Value : 基底型に変換する値
///
template <auto Value, class=std::enable_if_t<std::is_enum<decltype(Value)>::value>>
struct RawNumber
{
    using NumTy = std::underlying_type_t<decltype(Value)>;
    static constexpr NumTy value = static_cast<NumTy>(Value);
};

///
/// @brief   列挙子をその基底型に変換
/// @details 列挙子以外の引数は受け取りません。 <br>
///           変換したい値がコンパイル時に決まっていない場合でも変換可能です。
///
/// @return その基底型に変換した列挙子の値
///
template <class EnumType, class=std::enable_if_t<std::is_enum<EnumType>::value>>
constexpr std::underlying_type_t<EnumType> rawNumber( EnumType Value )
{
    return static_cast<std::underlying_type_t<EnumType>>( Value );
}

END_EGEG
#endif /// !INCLUDED_EGEG_RAW_NUMBER_HEADER_
/// EOF
