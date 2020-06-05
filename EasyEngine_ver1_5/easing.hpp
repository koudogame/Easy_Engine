///
/// @file   easing.hpp
/// @author 板場
///
/// @brief   イージング関数群
/// @details 下記にあるサイトを参考にして作成しました。 <br>
///           各関数の右に種類毎のページへのURLが記述されています。
///

// 参考サイト
//  https://easings.net/ja
// ライセンス
//  https://github.com/ai/easings.net/blob/master/LICENSE

#ifndef INCLUDED_EGEG_EASING_HEADER_
#define INCLUDED_EGEG_EASING_HEADER_

#include <corecrt_math_defines.h>
#include <cmath>
#include "egeg_def.hpp"

BEGIN_EGEG
namespace easing
{
    namespace impl
    {
    inline constexpr float pow( float X, int Y ) noexcept { return Y>0 ? X*pow(X,Y-1) : Y<0 ? 1.0F/pow(X, -Y) : 1.0F; }
    }

 // linear
inline constexpr float linear( float Time ) noexcept { return Time; }
 // sine
inline float easeInSine( float Time ) noexcept { return 1.0F - std::cos((Time*static_cast<float>(M_PI)) * 0.5F); } // https://easings.net/ja#easeInSine
inline float easeOutSine( float Time ) noexcept { return std::sin((Time*static_cast<float>(M_PI)) * 0.5F); } // https://easings.net/ja#easeOutSine
inline float easeInOutSine( float Time ) noexcept { return -(std::cos(Time*static_cast<float>(Time))-1.0F) * 0.5F; } // https://easings.net/ja#easeInOutSine
 // quad
inline constexpr float easeInQuad( float Time ) noexcept { return impl::pow(Time, 2); } // https://easings.net/ja#easeInQuad
inline constexpr float easeOutQuad( float Time ) noexcept { return 1.0F - impl::pow(1.0F-Time, 2); } // https://easings.net/ja#easeOutQuad
inline constexpr float easeInOutQuad( float Time ) noexcept { return Time<0.5F ? 2.0F*impl::pow(Time, 2) : 1.0F-impl::pow(-2.0F*Time+2.0F, 2)*0.5F; } // https://easings.net/ja#easeInOutQuad
 // cubic
inline constexpr float easeInCubic( float Time ) noexcept { return impl::pow(Time, 3); } // https://easings.net/ja#easeInCubic
inline constexpr float easeOutCubic( float Time ) noexcept { return 1.0F - impl::pow(1.0F-Time, 3); } // https://easings.net/ja#easeOutCubic
inline constexpr float easeInOutCubic( float Time ) noexcept { return Time<0.5F ? 4.0F*impl::pow(Time, 3) : 1.0F-impl::pow(-2.0F*Time+2.0F, 3)*0.5F; } // https://easings.net/ja#easeInOutCubic
 // quart
inline constexpr float easeInQuart( float Time ) noexcept { return impl::pow(Time, 4); } // https://easings.net/ja#easeInQuart
inline constexpr float easeOutQuart( float Time ) noexcept { return 1.0F - impl::pow(1.0F-Time, 4); } // https://easings.net/ja#easeOutQuart
inline constexpr float easeInOutQuart( float Time ) noexcept { return Time<0.5F ? 8.0F*impl::pow(Time, 4) : 1.0F-impl::pow(-2.0F*Time+2.0F, 4)*0.5F; } // https://easings.net/ja#easeInOutQuart
 // quint
inline constexpr float easeInQuint( float Time ) noexcept { return impl::pow(Time, 5); } // https://easings.net/ja#easeInQuint
inline constexpr float easeOutQuint( float Time ) noexcept { return 1.0F - impl::pow(1.0F-Time, 5); } // https://easings.net/ja#easeOutQuint
inline constexpr float easeInOutQuint( float Time ) noexcept { return Time<0.5F ? 16.0F*impl::pow(Time, 5) : 1.0F-impl::pow(-2.0F*Time+2.0F, 5)*0.5F; } // https://easings.net/ja#easeInOutQuint
 // expo
inline float easeInExpo( float Time ) noexcept { return Time==0.0F ? 0.0F : impl::pow(2.0F, static_cast<int>(10*Time-10)); } // https://easings.net/ja#easeInExpo
inline float easeOutExpo( float Time ) noexcept { return Time==1.0F ? 1.0F : 1.0F-impl::pow(2, -static_cast<int>(10.0F*Time));} // https://easings.net/ja#easeOutExpo
inline float easeInOutExpo( float Time ) noexcept { return Time==0.0F ? 0.0F : Time==1.0F ? 1.0F : Time<0.5F ? impl::pow(2, static_cast<int>(20*Time-10))*0.5F : (2.0F-impl::pow(2.0F, -static_cast<int>(20*Time+10)))*0.5F; } // https://easings.net/ja#easeInOutExpo
 // circ
inline float easeInCirc( float Time ) noexcept { return 1.0F - std::sqrt(1.0F-std::pow(Time, 2)); } // https://easings.net/ja#easeInCirc
inline float easeOutCirc( float Time ) noexcept { return std::sqrt(1.0F-std::pow(Time-1.0F, 2)); } // https://easings.net/ja#easeOutCirc
inline float easeInOutCirc( float Time ) noexcept { return Time<0.5F ? (1.0F-std::sqrt(1.0F-std::pow(2.0F*Time, 2)))*0.5F : (std::sqrt(1.0F-std::pow(-2.0F*Time+2.0F, 2))+1.0F)*0.5F; } // https://easings.net/ja#easeInOutCirc
 // back
inline constexpr float easeInBack( float Time ) noexcept { return 2.70158F*impl::pow(Time,3)-1.70158F*impl::pow(Time, 2); } // https://easings.net/ja#easeInBack
inline constexpr float easeOutBack( float Time ) noexcept { return 1.0F + 2.70158F*impl::pow(Time-1.0F, 3) + 1.70158F*impl::pow(Time-1.0F, 2); } // https://easings.net/ja#easeOutBack
inline constexpr float easeInOutBack( float Time ) noexcept { return Time<0.5F ? (impl::pow(2.0F*Time, 2)*(2.96107095F*2.0F*Time-1.96107095F))*0.5F : (impl::pow(2.0F*Time-2.0F, 2)*(2.96107095F*(Time*2.0F-2.0F)+1.96107095F)+2.0F)*0.5F; } // https://easings.net/ja#easeInOutBack
 // elastic
inline float easeInElastic( float Time ) noexcept { return Time==0.0F ? 0.0F : Time==1.0F ? 1.0F : -std::pow(2.0F, 10.0F*Time-10.0F)*std::sin((Time*10.0F-10.75F)*static_cast<float>(2.0*M_PI/3.0)); } // https://easings.net/ja#easeInElastic
inline float easeOutElastic( float Time ) noexcept { return Time==0.0F ? 0.0F : Time==1.0F ? 1.0F : std::pow( 2.0F, -10.0F*Time)*std::sin((Time*10.0F-0.75F)*static_cast<float>(2.0*M_PI/3.0))+1.0F; } // https://easings.net/ja#easeOutElastic
inline float easeInOutElastic( float Time ) noexcept { return Time==0.0F ? 0.0F : Time==1.0F ? 1.0F : Time<0.5F ? -(std::pow(2.0F, 20.0F*Time-10.0F)*std::sin((20.0F*Time-11.125F)*static_cast<float>(2.0*M_PI/4.5)))*0.5F : (std::pow(2.0F, -20.0F*Time+10.0F)*std::sin((20.0F*Time-11.125F)*static_cast<float>(2.0*M_PI/4.5)))*0.5F+1.0F; } // https://easings.net/ja#easeInOutElastic
 // bounce
inline constexpr float easeOutBounce( float Time ) noexcept { return Time<1.0F/2.75F ? 7.5625F*impl::pow(Time, 2) : Time<2.0F/2.75F ? 7.5625F*(Time-=1.5F/2.75F)*Time+0.75F : Time<2.5F/2.75F ? 7.5625F*(Time-=2.25F/2.75F)*Time+0.9375F : 7.5625F*(Time-=2.625F/2.75F)*Time+0.984375F; } // https://easings.net/ja#easeOutBounce
inline constexpr float easeInBounce( float Time ) noexcept { return 1.0F - easeOutBounce(1.0F-Time); } // https://easings.net/ja#easeInBounce
inline constexpr float easeInOutBounce( float Time ) noexcept { return Time<0.5F ? (1.0F-easeOutBounce(1.0F-2.0F*Time))*0.5F : (1.0F+easeOutBounce(2.0F*Time-1.0F))*0.5F; } // https://easings.net/ja#easeInOutBounce

} // namespace easing
END_EGEG
#endif /// !INCLUDED_EGEG_EASING_HEADER_
/// EOF
