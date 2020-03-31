///
/// @file   table.hpp
/// @author 板場
///
#ifndef INCLUDED_EG_EG_TABLE_HEADER_
#define INCLUDED_EG_EG_TABLE_HEADER_

#include <cstdint>
#include <tuple>
#include "egeg.hpp"

BEGIN_EGEG

///
/// @class  Field
/// @brief  Tableの要素となるフィールド
///
/// @tparam ElementType : フィールドが持つ要素の型
/// @tparam Index       : 同一の要素型を持つフィールドを識別するインデックス
///
template <class ElementType, uint32_t Index = 0U>
class Field
{
public :
    using ElemType = ElementType;

    void set( const ElemType& Elem ) noexcept
    {
        element_ = Elem;
    }
    void set( ElemType&& Elem ) noexcept
    {
        element_ = std::move( Elem );
    }

    const ElemType& get() const noexcept
    {
        return element_;
    }

private :
    ElemType element_;
};


///
/// @class   Table
/// @brief   テーブル
///
/// @tparam  FieldTypes : テーブルの要素となるフィールドリスト
///
/// @details フィールドリストに渡す型は Field<T,N>です。                        <br>
///          使用例 )                                                           <br>
///            宣言                                                             <br>
///             Table<Field<const char*, 0U>, Field<const char*, 1U>> table;    <br>
///                                                                             <br>
///            要素のセット                                                     <br>
///             table.set<Field<const char*, 0U>>( "texture1.png" );             <br>
///             table.set<Field<const char*, 1U>>( "texture2.png" );             <br>
///                                                                             <br>
///            要素の取得                                                       <br>
///             table.get<Field<const char*, 0U>>();
///
template <class ...FieldTypes>
class Table
{
public :
    Table() = default;
    Table( const Table& Lhs ) :
        table_( Lhs.table_ ) {}
    Table( Table&& Rhs ) :
        table_( std::move(Rhs.table_) ) {}

    Table& operator=( const Table& Lhs )
    {
        table_ = Lhs.table_;
        return *this;
    }
    Table& operator=( Table&& Rhs )
    {
        table_ = std::move(Rhs.table_);
        return *this;
    }

    template <class FieldType>
    void set( const typename FieldType::ElemType& Element ) noexcept
    {
        std::get<FieldType>(table_).set( Element );
    }
    template <class FieldType>
    void set( typename FieldType::ElemType&& Element ) noexcept
    {
        std::get<FieldType>(table_).set( std::move(Element) );
    }

    template <class FieldType>
    const typename FieldType::ElemType& get() const noexcept
    {
        return std::get<FieldType>(table_).get();
    }

private :
    std::tuple<FieldTypes...> table_;
};

END_EGEG
#endif /// !INCLUDED_EG_EG_TABLE_HEADER_
/// EOF
