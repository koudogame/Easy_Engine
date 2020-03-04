///
/// @file   application_status.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
#define INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
#include <ratio>
#include "egeg.hpp"
BEGIN_EGEG
/******************************************************************************

    定数の定義

******************************************************************************/
///< 水平方向の解像度
template <class T>
constexpr T kHorizontalResolution = static_cast<T>(1280U);
///< 垂直方向の解像度
template <class T>
constexpr T kVerticalResolution = static_cast<T>(720U);
///< １秒当たりのフレーム数
constexpr uintmax_t kFPS = 60ULL;

/******************************************************************************

    定数の取得処理等

******************************************************************************/
///
/// @brief  解像度の取得
///
/// @param[out] Horizontal : 水平解像度のバッファ
/// @param[out] Vertical   : 垂直解像度のバッファ
///
template <class T>
void getResolution( T* Horizontal, T* Vertical ) noexcept
{
    if( Horizontal ) *Horizontal = kHorizontalResolution<T>;
    if( Vertical )   *Vertical   = kVerticalResolution<T>;
}

///
/// @brief  FPSから1フレーム当たりの更新時間を取得する
///
/// @tparam Unit : 時間単位
///
template <class Unit = std::micro>
class TimePerFrame
{
public :
    using Ratio = std::ratio_divide<std::ratio<1,kFPS>, Unit>;
    static constexpr intmax_t value = Ratio::num / Ratio::den;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SETTINGS_HEADER_
/// EOF
