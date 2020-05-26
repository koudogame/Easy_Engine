///
/// @file   table.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TABLE_HEADER_
#define INCLUDED_EGEG_TABLE_HEADER_

#include <tuple>
#include <istream>
#include <sstream>
#include "egeg_def.hpp"

BEGIN_EGEG

///< Table前方前言
template <class ...FieldTypes>
class Table;
///< ストリーム入力演算前方宣言
template <class ...FieldTypes>
std::istream& operator>>( std::istream& Istream, Table<FieldTypes...>& Tbl );


///
/// @class  Table
/// @brief  テーブル
///
/// @details 文字列、もしくは入力ストリームから保持するフィールドを読み込むことができます。
///
template <class ...FieldTypes>
class Table
{
public :
    ///
    /// @brief  文字列からデータを読み込む
    ///
    /// @param[in] Data : データを読み込む文字列
    ///
    Table( const std::string& Data )
    {
        std::stringbuf buf{ Data };
        std::istream is{ &buf };
        is >> *this;
    }
    ///
    /// @brief  入力ストリームからデータを読み込む
    ///
    /// @param[in] DataStream : データを読み込むストリーム
    ///
    Table( std::istream& DataStream )
    {
        DataStream >> *this;
    }

    ///
    /// @brief  データを取得する
    ///
    /// @tparam Index : 読み込むデータのインデックス
    ///
    /// @return インデックスに対応したデータ
    ///
    template <size_t Index>
     constexpr std::tuple_element_t<Index, std::tuple<FieldTypes...>>&
        get() noexcept
    {
        return std::get<Index>( data_ );
    }
    template <size_t Index>
    _NODISCARD constexpr const std::tuple_element_t<Index, std::tuple<FieldTypes...>>&
        get() const noexcept
    {
        return std::get<Index>( data_ );
    }

private :
    std::tuple<FieldTypes...> data_;
};






namespace impl
{
///
/// @class  Extractor
/// @brief  データ抽出器
/// @note   テンプレートの部分特殊化を行うためにクラス定義にしている。
///
/// @tparam Index : 抽出するデータの番号
/// @tparam bool  : 読み込み末端フラグ
///
template <size_t Index, bool>
class Extractor
{
public :
    template <class ...FieldTypes>
    Extractor( std::istream& Istream, Table<FieldTypes...>& Tbl ) :
        istream_{ Istream }
    {
        Extractor<Index+1, (Index+2)==sizeof...(FieldTypes)>{ Istream >> Tbl.get<Index>(), Tbl };
    }
    operator std::istream&() const noexcept { return istream_; }
private :
    std::istream& istream_;
};
///< 末端用抽出器
template <size_t Index>
class Extractor<Index, true>
{
public :
    template <class ...FieldTypes>
    Extractor( std::istream& Istream, Table<FieldTypes...>& Tbl ) :
        istream_{ Istream }
    {
        Istream >> Tbl.get<Index>();
    }
    operator std::istream&() const noexcept { return istream_; }
private :
    std::istream& istream_;
};
}


///< ストリーム入力演算定義
template <class ...FieldTypes>
std::istream& operator>>( std::istream& Istream, Table<FieldTypes...>& Tbl )
{
    return impl::Extractor<0,1==sizeof...(FieldTypes)>{ Istream, Tbl };
}

END_EGEG
#endif /// !INCLUDED_EGEG_TABLE_HEADER_
/// EOF
