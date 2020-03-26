// 作成者 : 板場
#include "keyboard_controller.hpp"
#include "utility_function.hpp"

BEGIN_EGEG

namespace
{
    using CtrlerType = KeyboardController;
    constexpr CtrlerType::KeyType kVKStart = 0x08;
    constexpr CtrlerType::KeyType KVKLast  = enumToValue(CtrlerType::Keys::kCapsLock);
} // unnamed namespace

// KeyboardController 関数定義
/*===========================================================================*/
// コンストラクタ
KeyboardController::KeyboardController( const Keyboard* Device ) noexcept :
    device_( Device )
{
}

// 処理の削除
void KeyboardController::unregisterFunction( KeyboardController::Keys Key )
{
    auto find = function_list_.find( enumToValue(Key) );
    if( find != function_list_.end() )
    { // 削除対象の関数がある場合
        find->second = nullptr;
    }
}

// 更新処理
void KeyboardController::update()
{
    for( KeyType vk = kVKStart; vk <= KVKLast; ++vk )
    { // キーに対応した関数を呼び出す
        auto find = function_list_.find( vk );
        if( find != function_list_.end() )
        { // 対応した関数がある場合
            find->second(
                *(reinterpret_cast<const InputDevice::FlagType*>(&device_->getState()) +
                vk)
            );
        }
    }
}

END_EGEG
// EOF
