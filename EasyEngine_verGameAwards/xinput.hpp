///
/// @file   xinput.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_XINPUT_HEADER_
#define INCLUDED_EGEG_XINPUT_HEADER_
#include <Windows.h> ///< target platform
#include <Xinput.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  XInput
/// @brief  XInputデバイスの基底クラス
///
class XInput
{
public :
    using FlagType = unsigned char;

    ///< 入力状態判定フラグ
    enum InputState : FlagType
    {
        kNone     = 0U,     ///< 入力なし
        kInput    = 0b001,  ///< 入力あり
        kPressed  = 0b011,  ///< 入力あり(押された瞬間)
        kReleased = 0b100,  ///< 入力なし(離された瞬間)
    };

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

    ///
    /// @brief   コンストラクタ
    /// @details コントローラーのインデックスは[0 ~ 3]の範囲で指定して下さい。
    ///
    /// @param[in] UserIndex : コントローラーのインデックス
    ///
    XInput( DWORD UserIndex ) noexcept;

    ///< 入力状態更新
    void update() noexcept;

    ///< 入力状態取得
    const State& getState() const noexcept { return state_; }

    
    ///
    /// @brief  ボタンが押されているか判定
    ///
    /// @param[in] ButtonState : 判定するボタンの状態
    ///
    /// @return 押されている[ true ]　押されていない[ false ]
    ///
    static bool isInput( FlagType ButtonState ) noexcept { return ButtonState & InputState::kInput; }
    ///
    /// @brief  ボタンが押された瞬間か判定
    ///
    /// @param[in] ButtonState : 判定するボタンの状態
    ///
    /// @return 押された瞬間[ true ]　押された瞬間ではない[ false ]
    ///
    static bool isPressed( FlagType ButtonState ) noexcept { return ButtonState & InputState::kPressed; }
    ///
    /// @brief  ボタンが継続して押されているか判定
    ///
    /// @param[in] ButtonState : 判定するボタンの状態
    ///
    /// @return 継続して押されている[ true ]　継続して押されていない[ false ]
    ///
    static bool isHold( FlagType ButtonState ) noexcept { return ButtonState == InputState::kInput; }
    ///
    /// @brief  ボタンが離された瞬間か判定
    ///
    /// @param[in] ButtonState : 判定するボタンの状態
    ///
    /// @return 離された瞬間[ true ]　離された瞬間ではない[ false ]
    ///
    static bool isReleased( FlagType ButtonState ) noexcept { return ButtonState & InputState::kReleased; }

private :
    FlagType newState( WORD, WORD, int ) noexcept;
    float stickNormalize( SHORT, int ) noexcept;

    DWORD user_idx_;
    State state_{};
    _XINPUT_STATE last_state_{};
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_HEADER_
/// EOF
