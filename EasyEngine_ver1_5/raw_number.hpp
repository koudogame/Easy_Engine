///
/// @file   raw_number.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_RAW_NUMBER_HEADER_
#define INCLUDED_EGEG_RAW_NUMBER_HEADER_

#include <type_traits>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class   RawNumber
/// @brief   �񋓎q�����̊��^�ɕϊ�
/// @details �񋓎q�ȊO�̃p�����[�^�͎󂯎��܂���B
///
/// @tparam Value : ���^�ɕϊ�����l
///
template <auto Value, class=std::enable_if_t<std::is_enum<decltype(Value)>::value>>
struct RawNumber
{
    using NumTy = std::underlying_type_t<decltype(Value)>;
    static constexpr NumTy value = static_cast<NumTy>(Value);
};

///
/// @brief   �񋓎q�����̊��^�ɕϊ�
/// @details �񋓎q�ȊO�̈����͎󂯎��܂���B <br>
///           �ϊ��������l���R���p�C�����Ɍ��܂��Ă��Ȃ��ꍇ�ł��ϊ��\�ł��B
///
/// @return ���̊��^�ɕϊ������񋓎q�̒l
///
template <class EnumType, class=std::enable_if_t<std::is_enum<EnumType>::value>>
constexpr std::underlying_type_t<EnumType> rawNumber( EnumType Value )
{
    return static_cast<std::underlying_type_t<EnumType>>( Value );
}

END_EGEG
#endif /// !INCLUDED_EGEG_RAW_NUMBER_HEADER_
/// EOF
