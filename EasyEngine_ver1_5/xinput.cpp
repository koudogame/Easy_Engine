// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "xinput.hpp"


/******************************************************************************

	library

******************************************************************************/
#pragma comment( lib, "xinput.lib" )

BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
	constexpr float kTriggerToNorm = 1.0F / 255.0F;
    constexpr float triggerToNorm( float Value ) noexcept { return Value * kTriggerToNorm; }
	constexpr float kStickToNorm = 1.0F / 32767.0F;
	constexpr float stickToNorm( float Value ) noexcept { return Value * kStickToNorm; }
}


/******************************************************************************

	declaration

******************************************************************************/
InputDevice::InputType newState( WORD, WORD, int ) noexcept;
float stickToNormWithDeadZone( SHORT, int ) noexcept;


/******************************************************************************

	XInputImpl

******************************************************************************/
 // 更新
template <DWORD UserIndex>
void impl::XInputImpl<UserIndex>::update()
{
    _XINPUT_STATE new_state{};

	if( XInputGetState(UserIndex, &new_state) == ERROR_SUCCESS )
	{
	    state_.connected = true;

		const WORD kLast = last_state_.Gamepad.wButtons;
		const WORD kNew  = new_state.Gamepad.wButtons;
		state_.dpad_up        = newState( kLast, kNew, XINPUT_GAMEPAD_DPAD_UP );
		state_.dpad_down      = newState( kLast, kNew, XINPUT_GAMEPAD_DPAD_DOWN );
		state_.dpad_left      = newState( kLast, kNew, XINPUT_GAMEPAD_DPAD_LEFT );
		state_.dpad_right     = newState( kLast, kNew, XINPUT_GAMEPAD_DPAD_RIGHT );
		state_.start          = newState( kLast, kNew, XINPUT_GAMEPAD_START );
		state_.back           = newState( kLast, kNew, XINPUT_GAMEPAD_BACK );
		state_.left_thumb     = newState( kLast, kNew, XINPUT_GAMEPAD_LEFT_THUMB );
		state_.right_thumb    = newState( kLast, kNew, XINPUT_GAMEPAD_RIGHT_THUMB );
		state_.left_shoulder  = newState( kLast, kNew, XINPUT_GAMEPAD_LEFT_SHOULDER );
		state_.right_shoulder = newState( kLast, kNew, XINPUT_GAMEPAD_RIGHT_SHOULDER );
		state_.a              = newState( kLast, kNew, XINPUT_GAMEPAD_A );
		state_.b              = newState( kLast, kNew, XINPUT_GAMEPAD_B );
		state_.x              = newState( kLast, kNew, XINPUT_GAMEPAD_X );
		state_.y              = newState( kLast, kNew, XINPUT_GAMEPAD_Y );

		state_.left_trigger  = triggerToNorm( new_state.Gamepad.bLeftTrigger );
		state_.right_trigger = triggerToNorm( new_state.Gamepad.bRightTrigger );

		state_.left_thumb_x  = stickToNormWithDeadZone( new_state.Gamepad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE );
		state_.left_thumb_y  = stickToNormWithDeadZone( new_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE );
		state_.right_thumb_x = stickToNormWithDeadZone( new_state.Gamepad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE );
		state_.right_thumb_y = stickToNormWithDeadZone( new_state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE );
	}
	    
	last_state_ = new_state;
}


/******************************************************************************

	others

******************************************************************************/
 // ボタンの入力状態を比較して状態を取得する
InputDevice::InputType newState( WORD Last, WORD New, int Button ) noexcept
{
    if( !(Last&Button) && !(New&Button) )
		return InputDevice::kNone;
	if( (Last&Button) && (New&Button) )
		return InputDevice::kInput;
	if( Last & Button )
		return InputDevice::kReleased;

	return InputDevice::kInput | InputDevice::kPressed;
}


 // スティックの値を正規化( デッドゾーン適応 )
float stickToNormWithDeadZone( SHORT Raw, int DeadZone ) noexcept
{
    if( Raw < DeadZone && Raw > -DeadZone )
		return 0.0F;

	const float kNorm = stickToNorm( Raw );
	return kNorm < -1.0F ? 1.0F : kNorm;
}


template class impl::XInputImpl<0U>;
template class impl::XInputImpl<1U>;
template class impl::XInputImpl<2U>;
template class impl::XInputImpl<3U>;

END_EGEG
// EOF
