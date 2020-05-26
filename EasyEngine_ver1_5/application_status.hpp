///
/// @file   application_status.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
#define INCLUDED_EGEG_APPLICATION_STATUS_HEADER_

#include "egeg_def.hpp"

BEGIN_EGEG

template <class Type>
constexpr Type kWindowWidth = static_cast<Type>(1280);  ///< ウィンドウ横幅

template <class Type>
constexpr Type kWindowHeight = static_cast<Type>(720);  ///< ウィンドウ縦幅

template <class Type>
constexpr Type kFps = static_cast<Type>(60);            ///< フレームレート

END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_STATUS_HEADER_
/// EOF
