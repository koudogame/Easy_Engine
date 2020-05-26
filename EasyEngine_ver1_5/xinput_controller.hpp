///
/// @file   xinput_controller.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_

#include <type_traits>
#include <array>
#include <functional>
#include "controller.hpp"
#include "xinput.hpp"
#include "raw_number.hpp"

BEGIN_EGEG

///
/// @class   XInputController
/// @brief   XInputデバイス用コントローラー
/// @details 保持するデバイスに変更を加えないことを保証します。
///
class XInputController :
    public Controller
{
public :
    using ButtonFunctionType  = std::function<void(InputDevice::InputType)>;
    using TriggerFunctionType = std::function<void(float)>;
    using StickFunctionType   = std::function<void(float, float)>;

    enum class Buttons : size_t
    {
        kDpadUp,
        kDpadDown,
        kDpadLeft,
        kDpadRight,
        kStart,
        kBack,
        kLeftThumb,
        kRightThumb,
        kLeftShoulder,
        kRightShoulder,
        kA,
        kB,
        kX,
        kY
    };

    enum class Triggers : size_t
    {
        kLeftTrigger,
        kRightTrigger
    };

    enum class Sticks : size_t
    {
        kLeftStick,
        kRightStick
    };

    ///
    /// @brief コンストラクタ
    ///
    /// @param[in] Device : 入力を取得するデバイス
    ///
    XInputController( const XInput* Device ) noexcept;

    ///
    /// @brief デバイスのセット
    ///
    /// @param[in] Device : セットするデバイス
    ///
    void setDevice( const XInput* Device ) noexcept { device_ = Device; }
    ///
    /// @brief デバイス取得
    ///
    /// @return デバイス
    ///
    const XInput* getDevice() const noexcept { return device_; }

    ///
    /// @brief   ボタン入力に対する関数の追加( ラムダ式、非メンバ関数用 )
    /// @details 関数の引数には、入力の種類をXInput::FlagTypeで渡します。
    ///
    /// @param[in] Button   : 関数と紐づけるボタン
    /// @param[in] Function : 呼び出す関数
    ///
    template <class FunctionType>
    void registerFunction( Buttons Button, FunctionType&& Function ) { button_func_list_.at( rawNumber(Button) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   ボタン入力に対する関数の追加( メンバ関数用 )
    /// @details ラムダ用registerFunctionと同じ動作をします。
    ///
    /// @param[in] Button   : 関数と紐づけるボタン
    /// @param[in] Owner    : 関数を呼び出すオーナー
    /// @param[in] Function : 呼び出す関数
    ///
    template <class OwnerType>
    void registerFunction( Buttons Button, OwnerType* Owner, void(OwnerType::*Function)(InputDevice::InputType) ) { registerFunction( Button, std::bind(Function, Owner, std::placeholders::_1) ); }
    ///
    /// @brief  ボタンと関数の紐づけを解除
    ///
    /// @param[in] Button : 紐づけを解除するボタン
    ///
    void unregisterFunction( Buttons Button ) { button_func_list_.at( rawNumber(Button) ) = nullptr; }

    ///
    /// @brief   トリガー入力に対する関数の追加( ラムダ式、非メンバ関数用 )
    /// @details 関数の引数には、トリガーの入力値(XInputの定める範囲)を渡します。
    ///
    /// @param[in] Trigger  : 関数と紐づけるトリガー
    /// @param[in] Function : 呼び出す関数
    ///
    template <class FunctionType>
    void registerFunction( Triggers Trigger, FunctionType Function ) { trigger_func_list_.at( rawNumber(Trigger) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   トリガー入力に対する関数の追加( メンバ関数用 )
    /// @details ラムダ用registerFunctionと同じ動作をします。
    ///
    /// @param[in] Trigger  : 関数と紐づけるトリガー
    /// @param[in] Owner    : 関数を呼び出すオーナー
    /// @param[in] Function : 呼び出す関数
    ///
    template <class OwnerType>
    void registerFunction( Triggers Trigger, OwnerType* Owner, void(OwnerType::*Function)(float) ) { registerFunction( Trigger, std::bind(Function, Owner, std::placeholders::_1) ); }
    ///
    /// @brief  トリガーと関数の紐づけを解除
    ///
    /// @param[in] Trigger : 紐づけを解除するトリガー
    ///
    void unregisterFunction( Triggers Trigger ) { trigger_func_list_.at( rawNumber(Trigger) ) = nullptr; }

    ///
    /// @brief   スティック入力(押し倒し)に対する関数の追加( ラムダ式、非メンバ関数用 )
    /// @details 関数の引数には、スティックの入力値(XInputの定める範囲)を渡します。 <br>
    ///           第一引数 : スティックX軸の入力値 <br>
    ///           第二引数 : スティックY軸の入力値
    ///
    /// @param[in] Stick    : 関数と紐づけるスティック
    /// @param[in] Function : 呼び出す関数
    ///
    template <class FunctionType>
    void registerFunction( Sticks Stick, FunctionType&& Function ) { stick_func_list_.at( rawNumber(Stick) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   スティック入力(押し倒し)に対する関数の追加( メンバ関数用 )
    /// @details ラムダ用registerFunctionと同じ動作をします。
    ///
    /// @param[in] Stick    : 関数と紐づけるスティック
    /// @param[in] Owner    : 関数を呼び出すオーナー
    /// @param[in] Function : 呼び出す関数
    ///
    template <class OwnerType>
    void registerFunction( Sticks Stick, OwnerType* Owner, void(OwnerType::*Function)(float, float) ) { registerFunction( Stick, std::bind(Function, Owner, std::placeholders::_1, std::placeholders::_2) ); }
    ///
    /// @brief  スティックと関数の紐づけを解除
    ///
    /// @param[in] Stick : 紐づけを解除するスティック
    ///
    void unregisterFunction( Sticks Stick ) { stick_func_list_.at( rawNumber(Stick) ) = nullptr; }

// override
    void update() override;

private :
    const XInput* device_;
    std::array<ButtonFunctionType, 14U> button_func_list_;
    std::array<TriggerFunctionType, 2U> trigger_func_list_;
    std::array<StickFunctionType,   2U> stick_func_list_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
