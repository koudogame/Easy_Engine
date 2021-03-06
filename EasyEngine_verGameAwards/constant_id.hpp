///
/// @file   constant_id.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CONSTANT_ID_HEADER_
#define INCLUDED_EGEG_CONSTANT_ID_HEADER_

#include <cstdint>
#include "egeg.hpp"

BEGIN_EGEG

///
/// @class  ConstantID
/// @brief  定数値をIDとして取得するクラス
///
template <uint32_t ID>
class ConstantID
{
public :
    constexpr ConstantID() noexcept {}

    constexpr operator uint32_t() const noexcept
    {
        return ID;
    }
    constexpr uint32_t operator()() const noexcept
    {
        return *this;
    }
};

END_EGEG
#endif /// !INCLUDED_EGEG_CONSTANT_ID_HEADER_
/// EOF
