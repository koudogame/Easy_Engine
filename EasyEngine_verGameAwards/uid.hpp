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
class UID
{
public :
    ///
    /// @brief  型からIDを取得する
    ///
    /// @tparam Object : IDを取得するクラス型
    ///
    /// @return ID
    ///
    template <class Object>
    static uint32_t getID() noexcept { static uint32_t uid = reinterpret_cast<uint32_t>(&uid); return uid; }

    ///
    /// @brief  インスタンスからIDを取得する
    ///
    /// @tparam Object : IDを取得するクラス型(省略可)
    /// @param[in] : IDを取得するオブジェクトインスタンス
    ///
    /// @return ID
    ///
    template <class Object>
    static uint32_t getID( const Object& ) noexcept { return UID::getID<Object>(); }
};
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
