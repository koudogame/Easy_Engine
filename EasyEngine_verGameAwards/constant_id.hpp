///
/// @file   constant_id.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CONSTANT_ID_HEADER_
#define INCLUDED_EGEG_CONSTANT_ID_HEADER_

#include <cstdint>
#include "egeg.hpp"

BEGIN_EGEG

///
/// @class  ConstantID
/// @brief  �萔�l��ID�Ƃ��Ď擾����N���X
///
template <uint32_t ID>
class ConstantID final
{
public :
    constexpr ConstantID() noexcept {}
    constexpr operator uint32_t() const noexcept
    {
        return ID;
    }

    constexpr uint32_t operator()() const noexcept
    {
        return ID;
    }
};

END_EGEG
#endif /// !INCLUDED_EGEG_CONSTANT_ID_HEADER_
/// EOF
