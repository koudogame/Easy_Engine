///
/// @file   input_device.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_INPUT_DEVICE_HEADER_
#define INCLUDED_EGEG_INPUT_DEVICE_HEADER_
#include "egeg.hpp"
///
/// @class  InputDevice
/// @brief  入力取得関係の基底クラス
///
class InputDevice
{
public :
    using FlagType = unsigned char;

    ///< 入力状態判定フラグ
    enum InputState : FlagType
    {
        kNone     = 0U,     ///< 入力なし
        kInput    = 0b001,  ///< 入力あり
        kPressed  = 0b010,  ///< 入力あり(押された瞬間)
        kReleased = 0b100,  ///< 入力なし(離された瞬間)
    };

    ///
    /// @brief  入力状態の更新処理
    ///
    virtual void update() = 0;

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
};
#endif /// !INCLUDED_EGEG_INPUT_DEVICE_HEADER_
/// EOF
