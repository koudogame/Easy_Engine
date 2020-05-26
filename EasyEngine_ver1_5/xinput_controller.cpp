// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "xinput_controller.hpp"
#include <type_traits>


/******************************************************************************

	declaration & definition

******************************************************************************/
template <class FunctionType, class ...ArgTypes>
void safeCall( FunctionType& Function, ArgTypes&& ...Args ) { if( Function ) Function( std::forward<ArgTypes>(Args)... ); }


BEGIN_EGEG

/******************************************************************************

	XInputController

******************************************************************************/
 // コンストラクタ
XInputController::XInputController( const XInput* Device ) noexcept :
    device_{ Device }
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
    {
        safeCall( button_func_list_.at(rawNumber(Buttons::kDpadUp)), state.dpad_up );
        safeCall( button_func_list_.at(rawNumber(Buttons::kDpadDown)), state.dpad_down );
        safeCall( button_func_list_.at(rawNumber(Buttons::kDpadLeft)), state.dpad_left );
        safeCall( button_func_list_.at(rawNumber(Buttons::kDpadRight)), state.dpad_right );
        safeCall( button_func_list_.at(rawNumber(Buttons::kStart)), state.start );
        safeCall( button_func_list_.at(rawNumber(Buttons::kBack)), state.back );
        safeCall( button_func_list_.at(rawNumber(Buttons::kLeftThumb)), state.left_thumb );
        safeCall( button_func_list_.at(rawNumber(Buttons::kRightThumb)), state.right_thumb );
        safeCall( button_func_list_.at(rawNumber(Buttons::kLeftShoulder)), state.left_shoulder );
        safeCall( button_func_list_.at(rawNumber(Buttons::kRightShoulder)), state.right_shoulder );
        safeCall( button_func_list_.at(rawNumber(Buttons::kA)), state.a );
        safeCall( button_func_list_.at(rawNumber(Buttons::kB)), state.b );
        safeCall( button_func_list_.at(rawNumber(Buttons::kX)), state.x );
        safeCall( button_func_list_.at(rawNumber(Buttons::kY)), state.y );
        safeCall( trigger_func_list_.at(rawNumber(Triggers::kLeftTrigger)), state.left_trigger );
        safeCall( trigger_func_list_.at(rawNumber(Triggers::kRightTrigger)), state.right_trigger );
        safeCall( stick_func_list_.at(rawNumber(Sticks::kLeftStick)), state.left_thumb_x, state.left_thumb_y );
        safeCall( stick_func_list_.at(rawNumber(Sticks::kRightStick)), state.right_thumb_x, state.right_thumb_y );
    }
}

END_EGEG
// EOF
