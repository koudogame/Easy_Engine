// 作成者 : 板場
#include "xinput_controller.hpp"

BEGIN_EGEG
// XInputController 関数実装
/*===========================================================================*/
// コンストラクタ
XInputController::XInputController( const XInput* InputDevice ) noexcept :
    device_( InputDevice )
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
        callFuncSafe( buttons_func_.at(Buttons::kDpadUp), state.dpad_up );
        callFuncSafe( buttons_func_.at(Buttons::kDpadDown), state.dpad_down );
        callFuncSafe( buttons_func_.at(Buttons::kDpadLeft), state.dpad_left );
        callFuncSafe( buttons_func_.at(Buttons::kDpadRight), state.dpad_right );
        callFuncSafe( buttons_func_.at(Buttons::kStart), state.start );
        callFuncSafe( buttons_func_.at(Buttons::kBack), state.back );
        callFuncSafe( buttons_func_.at(Buttons::kLeftThumb), state.left_thumbstick );
        callFuncSafe( buttons_func_.at(Buttons::kRightThumb), state.right_thumbstick );
        callFuncSafe( buttons_func_.at(Buttons::kLeftShoulder), state.left_shoulder );
        callFuncSafe( buttons_func_.at(Buttons::kRightShoulder), state.right_shoulder );
        callFuncSafe( buttons_func_.at(Buttons::kA), state.a );
        callFuncSafe( buttons_func_.at(Buttons::kB), state.b );
        callFuncSafe( buttons_func_.at(Buttons::kX), state.x );
        callFuncSafe( buttons_func_.at(Buttons::kY), state.y );

        callFuncSafe( triggers_func_.at(Triggers::kLeftTrigger), state.left_trigger );
        callFuncSafe( triggers_func_.at(Triggers::kRightTrigger), state.right_trigger );

        callFuncSafe( sticks_func_.at(Sticks::kLeftStick), state.left_thumbstick_x, state.left_thumbstick_y );
        callFuncSafe( sticks_func_.at(Sticks::kRightStick), state.right_thumbstick_x, state.right_thumbstick_y );
    }
}
END_EGEG
// EOF
