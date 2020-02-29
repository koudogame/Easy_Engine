// 作成者 : 板場
#include "xinput_controller.hpp"

BEGIN_EGEG
// XInputController 関数実装
/*===========================================================================*/
// コンストラクタ
XInputController::XInputController( XInputController::DeviceType& InputDevice ) noexcept :
    device_( &InputDevice )
{
    buttons_func_.fill( nullptr );
    triggers_func_.fill( nullptr );
    sticks_func_.fill( nullptr );
}

// 更新
void XInputController::update()
{
    const XInput::State& state = device_->getState();

    if( state.connected )
    {   // 入力デバイスが接続されている
        callFuncSafe( buttons_func_, Buttons::kDpadUp, state.dpad_up );
        callFuncSafe( buttons_func_, Buttons::kDpadDown, state.dpad_down );
        callFuncSafe( buttons_func_, Buttons::kDpadLeft, state.dpad_left );
        callFuncSafe( buttons_func_, Buttons::kDpadRight, state.dpad_right );
        callFuncSafe( buttons_func_, Buttons::kStart, state.start );
        callFuncSafe( buttons_func_, Buttons::kBack, state.back );
        callFuncSafe( buttons_func_, Buttons::kLeftThumb, state.left_thumbstick );
        callFuncSafe( buttons_func_, Buttons::kRightThumb, state.right_thumbstick );
        callFuncSafe( buttons_func_, Buttons::kLeftShoulder, state.left_shoulder );
        callFuncSafe( buttons_func_, Buttons::kRightShoulder, state.right_shoulder );
        callFuncSafe( buttons_func_, Buttons::kA, state.a );
        callFuncSafe( buttons_func_, Buttons::kB, state.b );
        callFuncSafe( buttons_func_, Buttons::kX, state.x );
        callFuncSafe( buttons_func_, Buttons::kY, state.y );

        callFuncSafe( triggers_func_, Triggers::kLeftTrigger, state.left_trigger );
        callFuncSafe( triggers_func_, Triggers::kRightTrigger, state.right_trigger );

        callFuncSafe( sticks_func_, Sticks::kLeftStick, state.left_thumbstick_x, state.left_thumbstick_y );
        callFuncSafe( sticks_func_, Sticks::kRightStick, state.right_thumbstick_x, state.right_thumbstick_y );
    }
}
END_EGEG
// EOF
