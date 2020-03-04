///
/// @file   xinput.hpp
/// @author Βκ
///
#ifndef INCLUDED_EGEG_XINPUT_HEADER_
#define INCLUDED_EGEG_XINPUT_HEADER_
#include <Windows.h> ///< target platform
#include <Xinput.h>
#include "input_device.hpp"
BEGIN_EGEG
///
/// @class  XInput
/// @brief  XInputfoCX
///
class XInput :
    public InputDevice
{
public :
    ///< όΝσΤi[\’Μ
    struct State
    {
        bool connected; ///< true : Ϊ±@false : Ϊ±Θ΅

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

        float left_trigger;         ///< 0.0F ~ 1.0F ΜΝΝ
        float right_trigger;        ///< 0.0F ~ 1.0F ΜΝΝ

        float left_thumbstick_x;    ///< 0.0F ~ 1.0F ΜΝΝ
        float left_thumbstick_y;    ///< 0.0F ~ 1.0F ΜΝΝ
        float right_thumbstick_x;   ///< 0.0F ~ 1.0F ΜΝΝ
        float right_thumbstick_y;   ///< 0.0F ~ 1.0F ΜΝΝ
    };

    ///< όΝσΤζΎ
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
    void update() override;
};
using XInputP1 = XInputImpl<0U>;
using XInputP2 = XInputImpl<1U>;
using XInputP3 = XInputImpl<2U>;
using XInputP4 = XInputImpl<3U>;
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_HEADER_
/// EOF
