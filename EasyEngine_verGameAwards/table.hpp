///
/// @file   table.hpp
/// @author ��
///
#ifndef INCLUDED_EG_EG_TABLE_HEADER_
#define INCLUDED_EG_EG_TABLE_HEADER_

#include <cstdint>
#include <tuple>
#include "egeg.hpp"

BEGIN_EGEG

///
/// @class  Field
/// @brief  Table�̗v�f�ƂȂ�t�B�[���h
///
/// @tparam ElementType : �t�B�[���h�����v�f�̌^
/// @tparam Index       : ����̗v�f�^�����t�B�[���h�����ʂ���C���f�b�N�X
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
/// @brief   �e�[�u��
///
/// @tparam  FieldTypes : �e�[�u���̗v�f�ƂȂ�t�B�[���h���X�g
///
/// @details �t�B�[���h���X�g�ɓn���^�� Field<T,N>�ł��B                        <br>
///          �g�p�� )                                                           <br>
///            �錾                                                             <br>
///             Table<Field<const char*, 0U>, Field<const char*, 1U>> table;    <br>
///                                                                             <br>
///            �v�f�̃Z�b�g                                                     <br>
///             table.set<Field<const char*, 0U>>( "texture1.png" );             <br>
///             table.set<Field<const char*, 1U>>( "texture2.png" );             <br>
///                                                                             <br>
///            �v�f�̎擾                                                       <br>
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
