///
/// @file   table.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TABLE_HEADER_
#define INCLUDED_EGEG_TABLE_HEADER_

#include <tuple>
#include <istream>
#include <sstream>
#include "egeg_def.hpp"

BEGIN_EGEG

///< Table�O���O��
template <class ...FieldTypes>
class Table;
///< �X�g���[�����͉��Z�O���錾
template <class ...FieldTypes>
std::istream& operator>>( std::istream& Istream, Table<FieldTypes...>& Tbl );


///
/// @class  Table
/// @brief  �e�[�u��
///
/// @details ������A�������͓��̓X�g���[������ێ�����t�B�[���h��ǂݍ��ނ��Ƃ��ł��܂��B
///
template <class ...FieldTypes>
class Table
{
public :
    ///
    /// @brief  �����񂩂�f�[�^��ǂݍ���
    ///
    /// @param[in] Data : �f�[�^��ǂݍ��ޕ�����
    ///
    Table( const std::string& Data )
    {
        std::stringbuf buf{ Data };
        std::istream is{ &buf };
        is >> *this;
    }
    ///
    /// @brief  ���̓X�g���[������f�[�^��ǂݍ���
    ///
    /// @param[in] DataStream : �f�[�^��ǂݍ��ރX�g���[��
    ///
    Table( std::istream& DataStream )
    {
        DataStream >> *this;
    }

    ///
    /// @brief  �f�[�^���擾����
    ///
    /// @tparam Index : �ǂݍ��ރf�[�^�̃C���f�b�N�X
    ///
    /// @return �C���f�b�N�X�ɑΉ������f�[�^
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
/// @brief  �f�[�^���o��
/// @note   �e���v���[�g�̕������ꉻ���s�����߂ɃN���X��`�ɂ��Ă���B
///
/// @tparam Index : ���o����f�[�^�̔ԍ�
/// @tparam bool  : �ǂݍ��ݖ��[�t���O
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
///< ���[�p���o��
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


///< �X�g���[�����͉��Z��`
template <class ...FieldTypes>
std::istream& operator>>( std::istream& Istream, Table<FieldTypes...>& Tbl )
{
    return impl::Extractor<0,1==sizeof...(FieldTypes)>{ Istream, Tbl };
}

END_EGEG
#endif /// !INCLUDED_EGEG_TABLE_HEADER_
/// EOF
