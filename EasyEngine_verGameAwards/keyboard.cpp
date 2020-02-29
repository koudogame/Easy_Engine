// 作成者 : 板場
#include "keyboard.hpp"
#include "egeg_utility.hpp"

namespace
{
    uint8_t toScancode( LPARAM lParam ) noexcept { return ( lParam >> 16U ) & 0b11111111; }
    WPARAM getKeyDetails( WPARAM wParam, LPARAM lParam ) noexcept;

    constexpr WPARAM kVKProcessKey  = 0xE5; // 漢字、CapsLK の仮想キーコード
    constexpr uint8_t kScancodeLShift = 0b00101010;
    constexpr uint8_t kScancodeRShift = 0b00110110;
    constexpr uint8_t kScancodeKanji  = 0b00101001;
    constexpr uint8_t kScancodeCapsLOCK = 0b00111010;

    constexpr float kReciprocal8 = 1.0F / 8.0F;
} // unnamed namespace

BEGIN_EGEG
// Keyboard 関数定義
/*===========================================================================*/
// コンストラクタ
Keyboard::Keyboard() noexcept
{
    curr_state_ = state_0_;
    last_state_ = state_1_;
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

}

// キーの押下イベント処理
// 
// in Key : 押下されたキーのキーコード( 1 ~255 )
//
//  ・キーに対応したビットが入っている要素番号の取得
//      - Key / 8 で要素番号の取得を行っている。
//  ・マスクの作成
//      - 0b00000001 ~ 0b10000000 がマスクの範囲
//      - 0x01を最大7ビット左へシフトする可能性がある。この7という数字は % 8により導き出される
void Keyboard::keyDown( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << ((Key-1) % 8));
    
    curr_state_[elem] |= mask;
}

// キーの離上イベント処理
//
// in Key : 離上されたキーのキーコード( 1 ~ 255 )
void Keyboard::keyUp( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << ((Key-1) % 8));

    curr_state_[elem] &= ~mask;
}

// 新しい状態の取得
InputDevice::FlagType Keyboard::newState( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << ((Key-1) % 8));

    if( !(last_state_[elem] & mask) && !(curr_state_[elem] & mask) )
        return EnumToValue( InputState::kNone );
    else if( (last_state_[elem] & mask) && (curr_state_[elem] & mask) )
        return EnumToValue( InputState::kInput );
    else if( curr_state_[elem] & mask )
        return EnumToValue( InputState::kPressed ) | EnumToValue( InputState::kInput );
    else
        return EnumToValue( InputState::kReleased );
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
        break;
        // TODO : コントロールキーのスキャンコードを調べて
        //        左右の入力に対応する
        //return toScancode
    case VK_MENU :
        break;
        // TODO : Altキーの左右入力に対応する
    }

    return 0;
}
} // unnamed namespace
// EOF
