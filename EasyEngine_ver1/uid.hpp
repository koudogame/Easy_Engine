///
/// @file   uid.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_UID_HEADER_
#define INCLUDED_EGEG_UID_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  TypeID
///
/// @brief  クラス毎に固有のIDを生成
///
/// @tparam Object : IDを生成するクラス型
///
template <class Object>
class TypeID
{
public :
    ///
    /// @brief  オブジェクトの型に対応するUIDの取得
    ///
    /// @return TypeID
    ///
    static uint32_t getID() noexcept { static uint32_t uid = reinterpret_cast<uint32_t>(&uid); return uid; }
};
END_EGEG
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
