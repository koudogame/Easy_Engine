// 作成者 : 板場
#include "xinput_controller.hpp"

BEGIN_EGEG

// XInputController 関数実装
/*===========================================================================*/
// コンストラクタ
XInputController::XInputController( const XInput* InputDevice ) noexcept :
    device_( InputDevice )
{
    button_func_list_.fill( nullptr );
    trigger_func_list_.fill( nullptr );
    stick_func_list_.fill( nullptr );
}

// 更新
void XInputController::update()
{
    const XInput::State& state = device_->getState();

    if( state.connected )
    {   // 入力デバイスが接続されている
        callFuncSafe( button_func_list_, Buttons::kDpadUp, state.dpad_up );
        callFuncSafe( button_func_list_, Buttons::kDpadDown, state.dpad_down );
        callFuncSafe( button_func_list_, Buttons::kDpadLeft, state.dpad_left );
        callFuncSafe( button_func_list_, Buttons::kDpadRight, state.dpad_right );
        callFuncSafe( button_func_list_, Buttons::kStart, state.start );
        callFuncSafe( button_func_list_, Buttons::kBack, state.back );
        callFuncSafe( button_func_list_, Buttons::kLeftThumb, state.left_thumbstick );
        callFuncSafe( button_func_list_, Buttons::kRightThumb, state.right_thumbstick );
        callFuncSafe( button_func_list_, Buttons::kLeftShoulder, state.left_shoulder );
        callFuncSafe( button_func_list_, Buttons::kRightShoulder, state.right_shoulder );
        callFuncSafe( button_func_list_, Buttons::kA, state.a );
        callFuncSafe( button_func_list_, Buttons::kB, state.b );
        callFuncSafe( button_func_list_, Buttons::kX, state.x );
        callFuncSafe( button_func_list_, Buttons::kY, state.y );

        callFuncSafe( trigger_func_list_, Triggers::kLeftTrigger, state.left_trigger );
        callFuncSafe( trigger_func_list_, Triggers::kRightTrigger, state.right_trigger );

        callFuncSafe( stick_func_list_, Sticks::kLeftStick, state.left_thumbstick_x, state.left_thumbstick_y );
        callFuncSafe( stick_func_list_, Sticks::kRightStick, state.right_thumbstick_x, state.right_thumbstick_y );
    }
}

END_EGEG
// EOF
