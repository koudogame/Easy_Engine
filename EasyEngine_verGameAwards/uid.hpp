///
/// @file   uid.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_UID_HEADER_
#define INCLUDED_EGEG_UID_HEADER_
#include <cstdint>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  UID
/// @brief  �^��񂩂�ID���擾����N���X
/// 
template <class Object>
class UID final
{
public :
    constexpr UID() noexcept {}
    operator uint32_t() const noexcept
    {
        static const uint32_t uid = reinterpret_cast<uint32_t>(&uid);
        return uid;
    }
};
END_EGEG
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
