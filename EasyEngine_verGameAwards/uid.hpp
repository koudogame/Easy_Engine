///
/// @file   uid.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_UID_HEADER_
#define INCLUDED_EGEG_UID_HEADER_
#include <cstdint>
///
/// @class  UID
/// @brief  型情報からIDを取得するクラス
/// 
template <class Object>
class UID
{
public :
    operator uint32_t() const noexcept
    {
        static const uintptr_t uid = reinterpret_cast<uint32_t>(&uid);
        return uid;
    }
};
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
