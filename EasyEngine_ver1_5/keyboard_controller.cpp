// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "keyboard_controller.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    constexpr KeyboardController::KeyType kStartKey = 0x08;
    constexpr KeyboardController::KeyType kLastKey  = rawNumber(KeyboardController::Keys::kCapsLock);
}


/******************************************************************************

	KeyboardController

******************************************************************************/
 // コンストラクタ
KeyboardController::KeyboardController( const Keyboard* Device ) noexcept :
    device_{ Device }
{
}


 // 関数の登録解除
void KeyboardController::unregisterFunction( Keys Key )
{
    auto find = function_list_.find( rawNumber(Key) );
    if( find != function_list_.end() )
    {
        find->second = nullptr;
    }
}


 // 更新
void KeyboardController::update()
{
    for( KeyType vk = kStartKey; vk <= kLastKey; ++vk )
    {
        auto find = function_list_.find( vk );
        if( find != function_list_.end() )
        { // キーに対応した関数がある場合に呼び出す
            find->second(
                *(reinterpret_cast<const InputDevice::InputType*>(&device_->getState()) +
                vk)
            );
        }
    }
}

END_EGEG
/// EOF
