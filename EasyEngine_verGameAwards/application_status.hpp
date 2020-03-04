///
/// @file   application_status.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
#define INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
#include <ratio>
#include "egeg.hpp"
BEGIN_EGEG
/******************************************************************************

    �萔�̒�`

******************************************************************************/
///< ���������̉𑜓x
template <class T>
constexpr T kHorizontalResolution = static_cast<T>(1280U);
///< ���������̉𑜓x
template <class T>
constexpr T kVerticalResolution = static_cast<T>(720U);
///< �P�b������̃t���[����
constexpr uintmax_t kFPS = 60ULL;

/******************************************************************************

    �萔�̎擾������

******************************************************************************/
///
/// @brief  �𑜓x�̎擾
///
/// @param[out] Horizontal : �����𑜓x�̃o�b�t�@
/// @param[out] Vertical   : �����𑜓x�̃o�b�t�@
///
template <class T>
void getResolution( T* Horizontal, T* Vertical ) noexcept
{
    if( Horizontal ) *Horizontal = kHorizontalResolution<T>;
    if( Vertical )   *Vertical   = kVerticalResolution<T>;
}

///
/// @brief  FPS����1�t���[��������̍X�V���Ԃ��擾����
///
/// @tparam Unit : ���ԒP��
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
