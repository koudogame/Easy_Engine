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
#include "utility_function.hpp"

BEGIN_EGEG

///
/// @class   XInputController
/// @brief   XInput用コントローラー
/// @details 保持するデバイスに変更を加えないことを保証します。
///
class XInputController :
    public Controller
{
public :
    using ButtonsFunctionType  = std::function<void(InputDevice::FlagType)>;
    using TriggersFunctionType = std::function<void(float)>;
    using SticksFunctionType   = std::function<void(float, float)>;

    ///
    /// @enum   Buttons
    /// @brief  ボタンの種類列挙
    ///
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
    ///
    /// @enum   Triggers
    /// @brief  トリガーの種類列挙
    ///
    enum class Triggers : size_t
    {
        kLeftTrigger,
        kRightTrigger
    };
    ///
    /// @enum   Sticks
    /// @brief  スティックの種類列挙
    ///
    enum class Sticks : size_t
    {
        kLeftStick,
        kRightStick
    };

    ///< コンストラクタ
    XInputController( const XInput* InputDevice ) noexcept;

    ///
    /// @brief   ボタン入力に対する関数の追加( ラムダ式、非メンバ関数用 )
    /// @details 関数の引数には、入力の種類をXInput::FlagTypeで渡します。
    ///
    /// @param[in] Button   : 関数と紐づけるボタン
    /// @param[in] Function : 呼び出す関数
    ///
    template <class FunctionType>
    void registerFunction( Buttons Button, FunctionType&& Function ) { button_func_list_.at( enumToValue(Button) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   ボタン入力に対する関数の追加( メンバ関数用 )
    /// @details ラムダ用registerFunctionと同じ動作をします。
    ///
    /// @param[in] Button   : 関数と紐づけるボタン
    /// @param[in] Owner    : 関数を呼び出すオーナー
    /// @param[in] Function : 呼び出す関数
    ///
    template <class OwnerType>
    void registerFunction( Buttons Button, OwnerType* Owner, void(OwnerType::*Function)(InputDevice::FlagType) ) { registerFunction( Button, std::bind(Function, Owner, std::placeholders::_1) ); }
    ///
    /// @brief  ボタンと関数の紐づけを解除
    ///
    /// @param[in] Button : 紐づけを解除するボタン
    ///
    void unregisterFunction( Buttons Button ) { button_func_list_.at( enumToValue(Button) ) = nullptr; }
    ///
    /// @brief   トリガー入力に対する関数の追加( ラムダ式、非メンバ関数用 )
    /// @details 関数の引数には、トリガーの入力値(XInputの定める範囲)を渡します。
    ///
    /// @param[in] Trigger  : 関数と紐づけるトリガー
    /// @param[in] Function : 呼び出す関数
    ///
    template <class FunctionType>
    void registerFunction( Triggers Trigger, FunctionType&& Function ) { trigger_func_list_.at( enumToValue(Trigger) ) = std::forward<FunctionType>(Function); }
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
    void unregisterFunction( Triggers Trigger ) { trigger_func_list_.at( enumToValue(Trigger) ) = nullptr; }
    ///
    /// @brief   スティック入力(押し倒し)に対する関数の追加( ラムダ式、非メンバ関数用 )
    /// @details 関数の引数には、スティックの入力値(XInputの定める範囲)を渡します。<br>
    ///          第一引数 : スティックX軸の入力値<br>
    ///          第二引数 : スティックY軸の入力値
    ///
    /// @param[in] Stick    : 関数と紐づけるスティック
    /// @param[in] Function : 呼び出す関数
    ///
    template <class FunctionType>
    void registerFunction( Sticks Stick, FunctionType&& Function ) { stick_func_list_.at( enumToValue(Stick) ) = std::forward<FunctionType>(Function); }
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
    void unregisterFunction( Sticks Stick ) { stick_func_list_.at( enumToValue(Stick) ) = nullptr; }
    
    ///
    /// @brief  入力デバイスの設定
    ///
    /// @param[in] XInputDevice : 設定するデバイス
    ///
    void setDevice( const XInput* XInputDevice ) noexcept { device_ = XInputDevice; }
    ///
    /// @brief  入力デバイスの取得
    ///
    /// @return 入力デバイス
    ///
    const XInput& getDevice() const noexcept { return *device_; }
        
/*-----------------------------------------------------------------*/
// Controller
    void update() override;
/*-----------------------------------------------------------------*/

private :
    ///
    /// @param[in] Functions : 呼び出す関数群
    /// @param[in] Index     : 呼び出す関数を指定するインデックス
    /// @param[in] Args      : 呼び出す関数に渡す引数リスト
    ///
    template <class FuncList, class EnumType, class ...Ts>
    void callFuncSafe( FuncList& Functions, EnumType Index, Ts&& ...Args )
    {   // 安全な関数呼び出し
        if( auto func = Functions.at(enumToValue(Index)) ) func( std::forward<Ts>(Args)... );
    }

    const XInput* device_;
    std::array<ButtonsFunctionType, 14U> button_func_list_;
    std::array<TriggersFunctionType, 2U> trigger_func_list_;
    std::array<SticksFunctionType, 2U>   stick_func_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
