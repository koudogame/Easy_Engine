///
/// @file   utility_function.hpp
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
constexpr auto enumToValue( EnumClass Enumerator ) noexcept
{
    return static_cast<std::underlying_type_t<EnumClass>>(Enumerator);
}

END_EGEG
#endif /// !INCLUDED_EGEG_UTILITY_HEADER_
/// EOF
