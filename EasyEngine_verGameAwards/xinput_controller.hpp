///
/// @file   xinput_controller.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#include <array>
#include <type_traits>
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
    using DeviceType = const XInput;

    using ButtonsFunctionType  = void(*)( InputDevice::FlagType );
    using TriggersFunctionType = void(*)( float );
    using SticksFunctionType   = void(*)( float, float );

    template <class Elem, size_t Size>
    using FunctionList = std::array<Elem, Size>;


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
    XInputController( DeviceType& InputDevice ) noexcept;

    ///
    /// @brief   ボタン入力に対する関数の追加
    /// @details 関数の引数には、入力の種類をXInput::FlagTypeで渡します。
    ///
    /// @param[in] Button   ; 関数と紐づけるボタン
    /// @param[in] Function : 呼び出す関数
    ///
    void registerFunction( Buttons Button, ButtonsFunctionType Function ) { buttons_func_.at( EnumToValue(Button) ) = Function; }
    ///
    /// @brief  ボタンと関数の紐づけを解除
    ///
    /// @param[in] Button : 紐づけを解除するボタン
    ///
    void unregisterFunction( Buttons Button ) { buttons_func_.at( EnumToValue(Button) ) = nullptr; }
    ///
    /// @brief   トリガー入力に対する関数の追加
    /// @details 関数の引数には、トリガーの入力値(XInputの定める範囲)を渡します。
    ///
    /// @param[in] Trigger  : 関数と紐づけるトリガー
    /// @param[in] Function : 呼び出す関数
    ///
    void registerFunction( Triggers Trigger, TriggersFunctionType Function ) { triggers_func_.at( EnumToValue(Trigger) ) = Function; }
    ///
    /// @brief  トリガーと関数の紐づけを解除
    ///
    /// @param[in] Trigger : 紐づけを解除するトリガー
    ///
    void unregisterFunction( Triggers Trigger ) { triggers_func_.at( EnumToValue(Trigger) ) = nullptr; }
    ///
    /// @brief   スティック入力(押し倒し)に対する関数の追加
    /// @details 関数の引数には、スティックの入力値(XInputの定める範囲)を渡します。<br>
    ///          第一引数 : スティックX軸の入力値<br>
    ///          第二引数 : スティックY軸の入力値
    ///
    /// @param[in] Stick    : 関数と紐づけるスティック
    /// @param[in] Function : 呼び出す関数
    ///
    void registerFunction( Sticks Stick, SticksFunctionType Function ) { sticks_func_.at( EnumToValue(Stick) ) = Function; }
    ///
    /// @brief  スティックと関数の紐づけを解除
    ///
    /// @param[in] Stick : 紐づけを解除するスティック
    ///
    void unregisterFunction( Sticks Stick ) { sticks_func_.at( EnumToValue(Stick) ) = nullptr; }
    
    ///
    /// @brief  入力デバイスの設定
    ///
    /// @param[in] XInputDevice : 設定するデバイス
    ///
    void setDevice( DeviceType& XInputDevice ) noexcept { device_ = &XInputDevice; }
    ///
    /// @brief  入力デバイスの取得
    ///
    /// @return 入力デバイス
    ///
    DeviceType& getDevice() const noexcept { return *device_; }
        
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
    inline void callFuncSafe( FuncList& Functions, EnumType Index, Ts&& ...Args )
    {   // 安全な関数呼び出し
        if( auto func = Functions.at(EnumToValue(Index)) ) func( std::forward<Ts>(Args)... );
    }

    DeviceType* device_;
    FunctionList<ButtonsFunctionType, 14U> buttons_func_;
    FunctionList<TriggersFunctionType, 2U> triggers_func_;
    FunctionList<SticksFunctionType, 2U> sticks_func_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
