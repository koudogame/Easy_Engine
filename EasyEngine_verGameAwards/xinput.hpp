///
/// @file   xinput.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_XINPUT_HEADER_
#define INCLUDED_EGEG_XINPUT_HEADER_
#include <Windows.h> ///< target platform
#include <Xinput.h>
#include "input_device.hpp"
BEGIN_EGEG
///
/// @class   XInput
/// @brief   XInputデバイス
/// @details Singletonクラスです。インスタンス化は禁止しています。<br>
///          インスタンスへのアクセスはinstance関数を使用して下さい。
///
class XInput :
    public InputDevice
{
public :
    ///< 入力状態格納構造体
    struct State
    {
        bool connected; ///< true : 接続　false : 接続なし

        FlagType dpad_up;
        FlagType dpad_down;
        FlagType dpad_left;
        FlagType dpad_right;
        FlagType start;
        FlagType back;
        FlagType left_thumbstick;
        FlagType right_thumbstick;
        FlagType left_shoulder;
        FlagType right_shoulder;
        FlagType a;
        FlagType b;
        FlagType x;
        FlagType y;

        float left_trigger;         ///< 0.0F ~ 1.0F の範囲
        float right_trigger;        ///< 0.0F ~ 1.0F の範囲

        float left_thumbstick_x;    ///< 0.0F ~ 1.0F の範囲
        float left_thumbstick_y;    ///< 0.0F ~ 1.0F の範囲
        float right_thumbstick_x;   ///< 0.0F ~ 1.0F の範囲
        float right_thumbstick_y;   ///< 0.0F ~ 1.0F の範囲
    };

    ///< 入力状態取得
    const State& getState() const noexcept { return state_; }

    XInput& operator=( const XInput& ) = default;

protected :
    FlagType newState( WORD, WORD, int ) noexcept;
    float stickNormalize( SHORT, int ) noexcept;

    State state_{};
    _XINPUT_STATE last_state_{};
};


template <DWORD UserIdx>
class XInputImpl :
    public XInput
{
public :
    XInputImpl() = default;
    void update() override;
};

using XInputP1 = XInputImpl<0U>;    ///< ゲームパッド 0
using XInputP2 = XInputImpl<1U>;    ///< ゲームパッド 1
using XInputP3 = XInputImpl<2U>;    ///< ゲームパッド 2
using XInputP4 = XInputImpl<3U>;    ///< ゲームパッド 3

END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_HEADER_
/// EOF
