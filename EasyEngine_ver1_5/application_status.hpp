///
/// @file   application_status.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
#define INCLUDED_EGEG_APPLICATION_STATUS_HEADER_

#include <ratio>
#include "egeg_def.hpp"

BEGIN_EGEG

template <class Type>
constexpr Type kWindowWidth = static_cast<Type>(1280);      ///< �E�B���h�E����

template <class Type>
constexpr Type kWindowHeight = static_cast<Type>(720);      ///< �E�B���h�E�c��

template <class Type>
constexpr Type kFramePerSeconds = static_cast<Type>(60);    ///< �t���[�����[�g
template <class Type>
constexpr Type kFPS = kFramePerSeconds<Type>;

template <class Unit = std::milli>                          ///< 1�t���[��������̎���
constexpr uintmax_t kTimePerFrame = std::ratio_divide<std::ratio<1,kFPS<uintmax_t>>, Unit>::num/std::ratio_divide<std::ratio<1,kFPS<uintmax_t>>, Unit>::den;
template <class Unit = std::milli>
constexpr uintmax_t kTPF = kTimePerFrame<Unit>;

END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
/// EOF
