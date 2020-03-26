// 作成者 : 板場
#include "keyboard.hpp"
#include <cstdint>
#include "utility_function.hpp"
#include <cassert>

namespace
{
    uint16_t toScancode( LPARAM lParam ) noexcept { return ( lParam >> 16U ) & 0b1111111111111111; }
    WPARAM getKeyDetails( WPARAM wParam, LPARAM lParam ) noexcept;

    constexpr WPARAM kVKProcessKey  = 0xE5; // 漢字、CapsLK の仮想キーコード
    constexpr uint8_t kScancodeLShift = 0b00101010;
    constexpr uint8_t kScancodeRShift = 0b00110110;
    constexpr uint8_t kScancodeKanji  = 0b00101001;
    constexpr uint8_t kScancodeCapsLOCK = 0b00111010;
    constexpr uint16_t kExtensionBits = 0b0000000100000000;

    constexpr float kReciprocal8 = 1.0F / 8.0F;
} // unnamed namespace

BEGIN_EGEG
// Keyboard 関数定義
/*===========================================================================*/
// コンストラクタ
Keyboard::Keyboard() noexcept
{
    raw_.fill( 0 );
    last_.fill( 0 );
}

// イベント処理
void Keyboard::eventProcessing( UINT Mes, WPARAM wPrm, LPARAM lPrm ) noexcept
{
    switch( Mes )
    {
    case WM_SYSKEYDOWN :
    case WM_KEYDOWN :
        // 押下イベントの処理
        keyDown( ::getKeyDetails(wPrm, lPrm) );
        break;

    case WM_SYSKEYUP :
    case WM_KEYUP :
        // 離上イベントの処理
        keyUp( ::getKeyDetails(wPrm, lPrm) );
        break;
    }
}

// 更新処理
void Keyboard::update()
{
    for( size_t i = 0; i < 32U; ++i )
    { // 最新の状態と前回の状態を比較
        for( uint8_t j = 0; j < 8; ++j )
        { // 一つの変数の中にある8つのキーを比較
            uint8_t vk = static_cast<uint8_t>(i*8) + j;
            FlagType* ptr = reinterpret_cast<FlagType*>( &state_ ) + vk;
            *ptr = newState( vk );
        }
    }

    // 現在の状態と前回の状態として保存
    last_ = raw_;
}

// キーの押下イベント処理
// 
// in Key : 押下されたキーの仮想キーコード( 1 ~255 )
//
//  ・キーに対応したビットが入っている要素番号の取得
//      - Key / 8 で要素番号の取得を行っている。
//     
//  ・マスクの作成
//      - 0b00000001 ~ 0b10000000 がマスクの範囲
//      - 0x01を最大7ビット左へシフトする可能性がある。この7という数字は % 8(bit)により導き出される。
void Keyboard::keyDown( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << (Key % 8));
    
    raw_.at(elem) |= mask;
}

// キーの離上イベント処理
//
// in Key : 離上されたキーの仮想キーコード( 1 ~ 255 )
void Keyboard::keyUp( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = ~(0b00000001 << (Key % 8));
    
    raw_.at(elem) &= mask;
}

// 新しい状態の取得
InputDevice::FlagType Keyboard::newState( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << (Key % 8));

    auto isDown =
        [=](const std::array<uint8_t,32U>& State )
        {
            return State.at(elem) & mask;
        };

    if( !isDown(last_) && !isDown(raw_) )
    { // 入力無し
        return enumToValue( InputState::kNone );
    }
    else if( isDown(last_) && isDown(raw_) )
    { // 入力あり( 押下直後でない )
        return enumToValue( InputState::kInput );
    }
    else if( isDown(raw_) )
    { // 入力あり( 押下直後 )
        return enumToValue( InputState::kPressed ) | enumToValue( InputState::kInput );
    }
    else
    { // 入力なし( 離上直後 )
        return enumToValue( InputState::kReleased );
    }
}
END_EGEG

// unnamed namespace 関数定義
/*===========================================================================*/
namespace
{
// 詳細なキーコードを返却する
//
// in wParam : キーコード
// in lParam : スキャンコードを格納した値
//
// return 詳細なキーコード
WPARAM getKeyDetails( WPARAM wParam, LPARAM lParam ) noexcept
{
    switch( wParam )
    {
    case VK_SHIFT :
        return toScancode(lParam) == ::kScancodeLShift ? VK_LSHIFT : VK_RSHIFT;

    case VK_CONTROL :
        return toScancode(lParam) & ::kExtensionBits ? VK_RCONTROL : VK_LCONTROL;

    case VK_MENU :
        return toScancode(lParam) & ::kExtensionBits ? VK_RMENU : VK_LMENU;
    }

    return wParam;
}
} // unnamed namespace
// EOF
