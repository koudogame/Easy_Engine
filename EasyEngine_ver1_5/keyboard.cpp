// 作成者 : 板場
/******************************************************************************

	include
	
******************************************************************************/
#include "keyboard.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    constexpr uint16_t kExtensionBits = 0b0000000100000000;
    constexpr float kReciprocal8 = 1.0F / 8.0F;
    constexpr float divideBy8( float Value ) noexcept { return Value * kReciprocal8; }
}


/******************************************************************************

	declaration & definition

******************************************************************************/
uint16_t toScanCode( LPARAM lPrm ) noexcept { return (lPrm>>16U) & 0b1111111111111111; }
WPARAM getDetailedKey( WPARAM, LPARAM ) noexcept;
InputDevice::InputType newState( const std::array<uint8_t, 32U>&, const std::array<uint8_t, 32U>&, uint8_t ) noexcept;


/******************************************************************************

	Keyboard

******************************************************************************/
 // コンストラクタ
Keyboard::Keyboard() noexcept
{
    raw_.fill( 0 );
	last_.fill( 0 );
}


 // イベント処理
void Keyboard::eventProcessing( UINT Message, WPARAM wParam, LPARAM lParam ) noexcept
{
    switch( Message )
    {
    case WM_SYSKEYDOWN :
    case WM_KEYDOWN :
        keyDown( getDetailedKey(wParam, lParam) );
        break;
    case WM_SYSKEYUP :
    case WM_KEYUP :
        keyUp( getDetailedKey(wParam, lParam) );
        break;
    }
}


 // 更新
void Keyboard::update()
{
    for( size_t i = 0; i < 32U; ++i )
    { // 最新の状態と前回の状態を比較
        for( uint8_t j = 0; j < 8; ++j )
        { // 一つの変数の中にある8つのキーの状態を比較
            uint8_t vk = static_cast<uint8_t>(i*8) + j;
            InputType* ptr = reinterpret_cast<InputType*>( &state_ ) + vk;
            *ptr = newState( last_, raw_, vk );
        }
    }

    // 現在の状態を前回の状態として保存
    last_ = raw_;
}


 // キーの押下イベント処理
 //
 // in Key : 押下されたキー
void Keyboard::keyDown( uint8_t Key ) noexcept
{
    const unsigned kIndex = static_cast<unsigned>( divideBy8(Key) );
    const uint8_t kKeyBit = 0b00000001 << (Key % 8);

    raw_[kIndex] |= kKeyBit;
}
 // キーの離上イベント処理
void Keyboard::keyUp( uint8_t Key ) noexcept
{
    const unsigned kIndex = static_cast<unsigned>( divideBy8(Key) );
    const uint8_t kKeyBit = 0b00000001 << (Key % 8);

    raw_[kIndex] &= ~kKeyBit;
}


/******************************************************************************

	others

******************************************************************************/
 // スキャンコードから詳細なキーコードを取得する
WPARAM getDetailedKey( WPARAM wPrm, LPARAM lPrm ) noexcept
{
    switch( wPrm )
    {
    case VK_CONTROL :
        return toScanCode(lPrm) & kExtensionBits ? VK_RCONTROL : VK_LCONTROL;

    case VK_MENU :
        return toScanCode(lPrm) & kExtensionBits ? VK_RMENU : VK_LMENU;

    default :
        return wPrm;
    }
}


 // キーの入力状態を比較して状態を取得する
InputDevice::InputType newState( 
    const std::array<uint8_t, 32U>& Last,
    const std::array<uint8_t, 32U>& New,
    uint8_t Key ) noexcept
{
    const unsigned kIndex = static_cast<unsigned>( divideBy8(Key) );
    const uint8_t kKeyBit = 0b00000001 << (Key % 8);

    auto isDown = [=]( const std::array<uint8_t, 32U>& State )->uint8_t
    {
        return State[kIndex] & kKeyBit;
    };

    if( !isDown(Last) && !isDown(New) )
        return InputDevice::kNone;
    if( isDown(Last) && isDown(New) )
        return InputDevice::kInput;
    if( isDown(Last) )
        return InputDevice::kReleased;

    return InputDevice::kInput | InputDevice::kPressed;
}

END_EGEG
// EOF
