// �쐬�� : ��
#include "keyboard.hpp"
#include <cstdint>
#include "utility_function.hpp"
#include <cassert>

namespace
{
    uint16_t toScancode( LPARAM lParam ) noexcept { return ( lParam >> 16U ) & 0b1111111111111111; }
    WPARAM getKeyDetails( WPARAM wParam, LPARAM lParam ) noexcept;

    constexpr WPARAM kVKProcessKey  = 0xE5; // �����ACapsLK �̉��z�L�[�R�[�h
    constexpr uint8_t kScancodeLShift = 0b00101010;
    constexpr uint8_t kScancodeRShift = 0b00110110;
    constexpr uint8_t kScancodeKanji  = 0b00101001;
    constexpr uint8_t kScancodeCapsLOCK = 0b00111010;
    constexpr uint16_t kExtensionBits = 0b0000000100000000;

    constexpr float kReciprocal8 = 1.0F / 8.0F;
} // unnamed namespace

BEGIN_EGEG
// Keyboard �֐���`
/*===========================================================================*/
// �R���X�g���N�^
Keyboard::Keyboard() noexcept
{
    raw_.fill( 0 );
    last_.fill( 0 );
}

// �C�x���g����
void Keyboard::eventProcessing( UINT Mes, WPARAM wPrm, LPARAM lPrm ) noexcept
{
    switch( Mes )
    {
    case WM_SYSKEYDOWN :
    case WM_KEYDOWN :
        // �����C�x���g�̏���
        keyDown( ::getKeyDetails(wPrm, lPrm) );
        break;

    case WM_SYSKEYUP :
    case WM_KEYUP :
        // ����C�x���g�̏���
        keyUp( ::getKeyDetails(wPrm, lPrm) );
        break;
    }
}

// �X�V����
void Keyboard::update()
{
    for( size_t i = 0; i < 32U; ++i )
    { // �ŐV�̏�ԂƑO��̏�Ԃ��r
        for( uint8_t j = 0; j < 8; ++j )
        { // ��̕ϐ��̒��ɂ���8�̃L�[���r
            uint8_t vk = static_cast<uint8_t>(i*8) + j;
            FlagType* ptr = reinterpret_cast<FlagType*>( &state_ ) + vk;
            *ptr = newState( vk );
        }
    }

    // ���݂̏�ԂƑO��̏�ԂƂ��ĕۑ�
    last_ = raw_;
}

// �L�[�̉����C�x���g����
// 
// in Key : �������ꂽ�L�[�̉��z�L�[�R�[�h( 1 ~255 )
//
//  �E�L�[�ɑΉ������r�b�g�������Ă���v�f�ԍ��̎擾
//      - Key / 8 �ŗv�f�ԍ��̎擾���s���Ă���B
//     
//  �E�}�X�N�̍쐬
//      - 0b00000001 ~ 0b10000000 ���}�X�N�͈̔�
//      - 0x01���ő�7�r�b�g���փV�t�g����\��������B����7�Ƃ��������� % 8(bit)�ɂ�蓱���o�����B
void Keyboard::keyDown( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << (Key % 8));
    
    raw_.at(elem) |= mask;
}

// �L�[�̗���C�x���g����
//
// in Key : ���コ�ꂽ�L�[�̉��z�L�[�R�[�h( 1 ~ 255 )
void Keyboard::keyUp( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = ~(0b00000001 << (Key % 8));
    
    raw_.at(elem) &= mask;
}

// �V������Ԃ̎擾
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
    { // ���͖���
        return enumToValue( InputState::kNone );
    }
    else if( isDown(last_) && isDown(raw_) )
    { // ���͂���( ��������łȂ� )
        return enumToValue( InputState::kInput );
    }
    else if( isDown(raw_) )
    { // ���͂���( �������� )
        return enumToValue( InputState::kPressed ) | enumToValue( InputState::kInput );
    }
    else
    { // ���͂Ȃ�( ���㒼�� )
        return enumToValue( InputState::kReleased );
    }
}
END_EGEG

// unnamed namespace �֐���`
/*===========================================================================*/
namespace
{
// �ڍׂȃL�[�R�[�h��ԋp����
//
// in wParam : �L�[�R�[�h
// in lParam : �X�L�����R�[�h���i�[�����l
//
// return �ڍׂȃL�[�R�[�h
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
