///
/// @file   keyboard_controller.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_KEYBOARD_CONTROLLER_HEADER_
#define INCLUDED_EGEG_KEYBOARD_CONTROLLER_HEADER_

#include <unordered_map>
#include <functional>
#include "controller.hpp"
#include "keyboard.hpp"
#include "raw_number.hpp"

BEGIN_EGEG

///
/// @class   KeyboardController
/// @brief   キーボード用コントローラー
/// @details 保持するデバイスに変更を加えないことを保証します。 <br>
///           登録する関数は「戻り値void」「引数InputDevice::InputType」という条件を満たしてください。 <br>
///           登録された関数の引数には、入力の状態を渡します。
///
class KeyboardController :
    public Controller
{
public :
    using KeyType = uint8_t;
    using FunctionType = std::function<void(InputDevice::InputType)>;

    enum class Keys : KeyType
    {
        kBackspace = 0x08,
        kTab,
        kEnter = 0x0D,
        kEscape = 0x1B,
        kSpace = 0x20,
        kLeft = 0x25,
        kUp,
        kRight,
        kDown,
        k0 = 0x30,
        k1,
        k2,
        k3,
        k4,
        k5,
        k6,
        k7,
        k8,
        k9,
        kA = 0x41,
        kB,
        kC,
        kD,
        kE,
        kF,
        kG,
        kH,
        kI,
        kJ,
        kK,
        kL,
        kM,
        kN,
        kO,
        kP,
        kQ,
        kR,
        kS,
        kT,
        kU,
        kV,
        kW,
        kX,
        kY,
        kZ,
        kNum0 = 0x60,
        kNum1,
        kNum2,
        kNum3,
        kNum4,
        kNum5,
        kNum6,
        kNum7,
        kNum8,
        kNum9,
        kF1 = 0x70,
        kF2,
        kF3,
        kF4,
        kF5,
        kF6,
        kF7,
        kF8,
        kF9,
        kF10,
        kF11,
        kF12,
        kLShift = 0xA0,
        kRShift,
        kLCtrl,
        kRCtrl,
        kLAlt,
        kRAlt,
        kColon = 0xBA,
        kSemiColon,
        kMinus,
        kPeriod,
        kSlash,
        kAtmark,
        kLSquareBracket = 0xDB,
        kBackSlash,
        kRSquareBracket,
        kCaret,
        kCapsLock = 0xF0,
    };

    ///
    /// @brief コンストラクタ
    ///
    /// @param[in] Device : 入力を取得するデバイス
    ///
    KeyboardController( const Keyboard* Device ) noexcept;

    ///
    /// @brief   キーに対応する処理の追加( ラムダ式、非メンバ関数用 )
    /// @details 既に処理が登録されている場合、上書きします。
    ///
    /// @param[in] Key      : 処理と紐づけるキー
    /// @param[in] Function : キーに紐づける処理
    ///
    template <class FunctionType_>
    void registerFunction( Keys Key, FunctionType_&& Function )
    {
        function_list_[rawNumber(Key)] = std::forward<FunctionType_>(Function);
    }
    ///
    /// @brief   キーに対応する処理の追加( メンバ関数用 )
    /// @details ラムダ用registerFunctionと同じ動作をします。
    ///
    /// @param[in] Key      : 処理と紐づけるキー
    /// @param[in] Owner    : 処理を呼び出すオーナー
    /// @param[in] Function : キーに紐づける処理
    ///
    template <class OwnerType>
    void registerFunction( Keys Key, OwnerType* Owner, void(OwnerType::*Function)(InputDevice::InputType) )
    {
        registerFunction( Key, std::bind(Function, Owner, std::placeholders::_1) );
    }
    ///
    /// @brief   キーに対応する処理の削除
    /// @details 引数のキーに対応した処理が無い場合、何も行いません。 <br>
    ///           registerFunction( Key, nullptr )とした場合と動作が異なります。
    ///
    /// @param[in] Key : 削除する処理に対応したキー
    ///
    void unregisterFunction( Keys Key );

// override
    void update() override;

private :
    const Keyboard* device_;
    std::unordered_map<KeyType, FunctionType> function_list_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_KEYBOARD_CONTROLLER_HEADER_
/// EOF
