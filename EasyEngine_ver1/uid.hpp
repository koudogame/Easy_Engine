///
/// @file   uid.hpp
/// @author 板場
///
/// @brief  クラス毎に固有のIDを取得する
///
/// @tparam Object : IDを取得するクラス型
///
#ifndef INCLUDED_EGEG_UID_HEADER_
#define INCLUDED_EGEG_UID_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
template <class Object>
class UID
{
public :
    ///
    /// @brief  UIDの取得
    ///
    /// @return UID
    ///
    static uint32_t get() noexcept { static uint32_t uid = reinterpret_cast<uint32_t>(&uid); return uid; }
};
END_EGEG
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
