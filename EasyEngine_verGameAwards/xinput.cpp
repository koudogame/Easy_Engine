// 作成者 : 板場7
#include "xinput.hpp"
#include <cassert>
#include <xutility>
#include "egeg_utility.hpp"
#pragma comment( lib, "xinput.lib" )

namespace
{
    constexpr float kTriggerToNorm = 1.0F / 255.0F;
    constexpr float kStickToNorm = 1.0F / 32767.0F;
} // unnamed namespace

BEGIN_EGEG
// XInput 関数定義
/*===========================================================================*/
// 新しい状態の取得
//
// in Last : 前回の状態
// in Curr : 現在の状態
// in ButtonFlag : 状態を取得するボタンの種類( XINPUT_GAMEPAD_~~ )
//
// return 状態
InputDevice::FlagType XInput::newState( WORD Last, WORD Curr, int ButtonFlag ) noexcept
{
    if( !(Last & ButtonFlag) && !(Curr & ButtonFlag) )
        return EnumToValue( InputState::kNone );
    else if( (Last & ButtonFlag) && (Curr & ButtonFlag) )
        return EnumToValue( InputState::kInput );
    else if( Curr & ButtonFlag )
        return EnumToValue(InputState::kInput) | EnumToValue(InputState::kPressed);
    else
        return EnumToValue( InputState::kReleased );
}

// スティックの値を正規化
//
// in Raw : 正規化前の値
// in DeadZone : デッドゾーン
//
// return 正規化後の値
float XInput::stickNormalize( SHORT Raw, int DeadZone ) noexcept
{
    if( Raw < DeadZone && Raw > -DeadZone )
        return 0.0F;
    else
    {
        float norm = Raw * ::kStickToNorm;
        if( norm < -1.0F )
            norm = -1.0F;

        return norm;
    }
}


// XInputImpl 関数定義
/*===========================================================================*/
// 入力更新
template <DWORD UserIdx>
void XInputImpl<UserIdx>::update()
{
    _XINPUT_STATE curr_state = {};

    if( XInputGetState(UserIdx, &curr_state) == ERROR_SUCCESS )
    {
        // 接続している
        state_.connected = true;

        // ボタン更新
        WORD last_button = last_state_.Gamepad.wButtons;
        WORD curr_button = curr_state.Gamepad.wButtons;
        state_.dpad_up = newState( last_button, curr_button, XINPUT_GAMEPAD_DPAD_UP );
        state_.dpad_down = newState( last_button, curr_button, XINPUT_GAMEPAD_DPAD_DOWN );
        state_.dpad_left = newState( last_button, curr_button, XINPUT_GAMEPAD_DPAD_LEFT );
        state_.dpad_right = newState( last_button, curr_button, XINPUT_GAMEPAD_DPAD_RIGHT );
        state_.start = newState( last_button, curr_button, XINPUT_GAMEPAD_START );
        state_.back = newState( last_button, curr_button, XINPUT_GAMEPAD_BACK );
        state_.left_thumbstick = newState( last_button, curr_button, XINPUT_GAMEPAD_LEFT_THUMB );
        state_.right_thumbstick = newState( last_button, curr_button, XINPUT_GAMEPAD_RIGHT_THUMB );
        state_.left_shoulder = newState( last_button, curr_button, XINPUT_GAMEPAD_LEFT_SHOULDER );
        state_.right_shoulder = newState( last_button, curr_button, XINPUT_GAMEPAD_RIGHT_SHOULDER );
        state_.a = newState( last_button, curr_button, XINPUT_GAMEPAD_A );
        state_.b = newState( last_button, curr_button, XINPUT_GAMEPAD_B );
        state_.x = newState( last_button, curr_button, XINPUT_GAMEPAD_X );
        state_.y = newState( last_button, curr_button, XINPUT_GAMEPAD_Y );

        // トリガー更新
        state_.left_trigger = curr_state.Gamepad.bLeftTrigger * ::kTriggerToNorm;
        state_.right_trigger = curr_state.Gamepad.bRightTrigger * ::kTriggerToNorm;

        // スティック更新
        state_.left_thumbstick_x = stickNormalize( curr_state.Gamepad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE );
        state_.left_thumbstick_y = stickNormalize( curr_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE );
        state_.right_thumbstick_x = stickNormalize( curr_state.Gamepad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE );
        state_.right_thumbstick_y = stickNormalize( curr_state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE );
    }
    else
    {
        // 接続していない
        state_.connected = false;
    }

    last_state_ = std::move( curr_state );
}

// 明示的なテンプレートのインスタンス化
template class XInputImpl<0U>;
template class XInputImpl<1U>;
template class XInputImpl<2U>;
template class XInputImpl<3U>;
END_EGEG
// EOF
