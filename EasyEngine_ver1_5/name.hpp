///
/// @file   name.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_NAME_HEADER_
#define INCLUDED_EGEG_NAME_HEADER_

#include <string>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @struct  Name
/// @brief   �������ԋp����t�@���N�^
/// @details ���� Name<"hoge">�̂悤�ɐ錾�ł��Ȃ��B                  <br>
///          �������ݒ肷��ۂ́A�萔�Ƃ��Ē�`�����セ�̒萔��n���܂��B <br>
///          �g�p�� )                                                <br>
///           �錾                                                  <br>
///             static constexpr const char kHogeName = "hoge";     <br>
///             Name<kHogeName> name_generator{};
///
template <const char Name_[]>
struct Name
{
    std::string operator()() const noexcept
    {
        return std::string{ Name_ };
    }
};

END_EGEG
#endif /// !INCLUDED_EGEG_NAME_HEADER_
/// EOF
