///
/// @file   xinput.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_XINPUT_HEADER_
#define INCLUDED_EGEG_XINPUT_HEADER_

#include <Windows.h>
#include <Xinput.h>
#include "input_device.hpp"

BEGIN_EGEG

///
/// @class   XInput
/// @brief   XInput�f�o�C�X
///
class XInput :
    public InputDevice
{
public :
    struct State
    {
        bool connected; ///< true : �ڑ�����@false : �ڑ��Ȃ�
        InputType dpad_up;
        InputType dpad_down;
        InputType dpad_left;
        InputType dpad_right;
        InputType start;
        InputType back;
        InputType left_thumb;
        InputType right_thumb;
        InputType left_shoulder;
        InputType right_shoulder;
        InputType a;
        InputType b;
        InputType x;
        InputType y;
        float left_trigger;     ///< 0.0 ~ 1.0 �͈͓̔�
        float right_trigger;    ///< 0.0 ~ 1.0 �͈͓̔�
        float left_thumb_x;     ///< 0.0 ~ 1.0 �͈͓̔�
        float left_thumb_y;     ///< 0.0 ~ 1.0 �͈͓̔�
        float right_thumb_x;    ///< 0.0 ~ 1.0 �͈͓̔�
        float right_thumb_y;    ///< 0.0 ~ 1.0 �͈͓̔�
    };

    ///
    /// @brief ���͏�Ԃ̎擾
    ///
    const State& getState() const noexcept { return state_; }

protected :
    State state_{};
    _XINPUT_STATE last_state_{};
};


namespace impl
{
template <DWORD UserIndex>
class XInputImpl :
    public XInput
{
public :
    XInputImpl() = default;

// override
    void update() override;
};
}
using XInputP1 = impl::XInputImpl<0U>;
using XInputP2 = impl::XInputImpl<1U>;
using XInputP3 = impl::XInputImpl<2U>;
using XInputP4 = impl::XInputImpl<3U>;

END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_HEADER_
/// EOF
