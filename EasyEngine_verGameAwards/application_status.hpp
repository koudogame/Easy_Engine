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
constexpr unsigned kHorizontalResolution = 1280U;
///< ���������̉𑜓x
constexpr unsigned kVerticalResolution = 720U;
///< �P�b������̃t���[����
constexpr uintmax_t kFPS = 60ULL;

/******************************************************************************

    �萔�̎擾������

******************************************************************************/
///
/// @brief  �����𑜓x�̎擾
///
/// @tparam T : �߂�l�^
///
/// @return �����𑜓x
///
template <class T = unsigned>
constexpr T getHorizontalResolution() noexcept
{
    return static_cast<T>( kHorizontalResolution );
}
///
/// @brief  �����𑜓x�̎擾
///
/// @tparam T : �߂�l�^
///
/// @return �����𑜓x
///
template <class T = unsigned>
constexpr T getVerticalResolution() noexcept
{
    return static_cast<T>( kVerticalResolution );
}
///
/// @brief  �𑜓x�̎擾
///
/// @tparam T : �𑜓x���擾����l�^
///
/// @param[out] Horizontal : �����𑜓x�̃o�b�t�@
/// @param[out] Vertical   : �����𑜓x�̃o�b�t�@
///
template <class T>
void getResolution( T* Horizontal, T* Vertical ) noexcept
{
    if( Horizontal ) *Horizontal = getHorizontalResolution<T>();
    if( Vertical )   *Vertical   = getVerticalResolution<T>();
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
