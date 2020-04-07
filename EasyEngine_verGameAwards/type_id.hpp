///
/// @file   type_id.hpp
/// @author ”Âê
///
#ifndef INCLUDED_EGEG_TYPE_ID_HEADER_
#define INCLUDED_EGEG_TYPE_ID_HEADER_

#include <cstdint>
#include "egeg.hpp"

BEGIN_EGEG

///
/// @class  TypeID
/// @brief  Œ^î•ñ‚©‚çID‚ğæ“¾‚·‚éƒNƒ‰ƒX
/// 
template <class Object>
class TypeID final
{
public :
    constexpr TypeID() noexcept {}
    operator uint32_t() const noexcept
    {
        static const uint32_t uid = reinterpret_cast<uint32_t>(&uid);
        return uid;
    }
    uint32_t operator()() const noexcept
    {
        return *this;
    }
};

END_EGEG
#endif /// !INCLUDED_EGEG_TYPE_ID_HEADER_
/// EOF
