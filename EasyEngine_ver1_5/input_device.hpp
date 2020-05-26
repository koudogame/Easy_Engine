///
/// @file   input_device.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_INPUT_DEVICE_HEADER_
#define INCLUDED_EGEG_INPUT_DEVICE_HEADER_

#include <cstdint>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class InputDevice
/// @brief 入力デバイス基底クラス
///
class InputDevice
{
public :
    using InputType = uint8_t;

    enum InputState : InputType
    {
        kNone     = 0b000, ///< 入力なし
        kInput    = 0b001, ///< 入力あり
        kPressed  = 0b010, ///< 入力あり( 押された瞬間 )
        kReleased = 0b100  ///< 入力なし( 離された瞬間 )
    };

    virtual ~InputDevice() = default;

    ///
    /// @brief 入力状態の更新
    ///
    virtual void update() = 0;

    ///
    /// @brief 入力があるか確認
    ///
    /// @param[in] State : 判定する状態
    ///
    /// @return true : ある　false : ない
    ///
    static bool isInput( InputType State ) noexcept { return State & kInput; }
    ///
    /// @brief 入力があった瞬間か確認
    ///
    /// @param[in] State : 判定する状態
    ///
    /// @return true : そう　false : そうでない
    ///
    static bool isPressed( InputType State ) noexcept { return State & kPressed; }
    ///
    /// @brief 入力が継続されているか確認
    ///
    /// @param[in] State : 判定する状態
    ///
    /// @return true : そう　false : そうでない
    ///
    static bool isHold( InputType State ) noexcept { return State == kInput; }
    ///
    /// @brief 入力が無くなった瞬間か確認
    ///
    /// @param[in] State : 判定する状態
    ///
    /// @return true : そう　false : そうでない
    ///
    static bool isReleased( InputType State ) noexcept { return State & kReleased; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_INPUT_DEVICE_HEADER_
/// EOF
