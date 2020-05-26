// �쐬�� : ��
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
 // �R���X�g���N�^
Keyboard::Keyboard() noexcept
{
    raw_.fill( 0 );
	last_.fill( 0 );
}


 // �C�x���g����
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


 // �X�V
void Keyboard::update()
{
    for( size_t i = 0; i < 32U; ++i )
    { // �ŐV�̏�ԂƑO��̏�Ԃ��r
        for( uint8_t j = 0; j < 8; ++j )
        { // ��̕ϐ��̒��ɂ���8�̃L�[�̏�Ԃ��r
            uint8_t vk = static_cast<uint8_t>(i*8) + j;
            InputType* ptr = reinterpret_cast<InputType*>( &state_ ) + vk;
            *ptr = newState( last_, raw_, vk );
        }
    }

    // ���݂̏�Ԃ�O��̏�ԂƂ��ĕۑ�
    last_ = raw_;
}


 // �L�[�̉����C�x���g����
 //
 // in Key : �������ꂽ�L�[
void Keyboard::keyDown( uint8_t Key ) noexcept
{
    const unsigned kIndex = static_cast<unsigned>( divideBy8(Key) );
    const uint8_t kKeyBit = 0b00000001 << (Key % 8);

    raw_[kIndex] |= kKeyBit;
}
 // �L�[�̗���C�x���g����
void Keyboard::keyUp( uint8_t Key ) noexcept
{
    const unsigned kIndex = static_cast<unsigned>( divideBy8(Key) );
    const uint8_t kKeyBit = 0b00000001 << (Key % 8);

    raw_[kIndex] &= ~kKeyBit;
}


/******************************************************************************

	others

******************************************************************************/
 // �X�L�����R�[�h����ڍׂȃL�[�R�[�h���擾����
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


 // �L�[�̓��͏�Ԃ��r���ď�Ԃ��擾����
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
