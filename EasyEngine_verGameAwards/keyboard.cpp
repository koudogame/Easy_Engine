// �쐬�� : ��
#include "keyboard.hpp"
#include "egeg_utility.hpp"

namespace
{
    uint8_t toScancode( LPARAM lParam ) noexcept { return ( lParam >> 16U ) & 0b11111111; }
    WPARAM getKeyDetails( WPARAM wParam, LPARAM lParam ) noexcept;

    constexpr WPARAM kVKProcessKey  = 0xE5; // �����ACapsLK �̉��z�L�[�R�[�h
    constexpr uint8_t kScancodeLShift = 0b00101010;
    constexpr uint8_t kScancodeRShift = 0b00110110;
    constexpr uint8_t kScancodeKanji  = 0b00101001;
    constexpr uint8_t kScancodeCapsLOCK = 0b00111010;

    constexpr float kReciprocal8 = 1.0F / 8.0F;
} // unnamed namespace

BEGIN_EGEG
// Keyboard �֐���`
/*===========================================================================*/
// �R���X�g���N�^
Keyboard::Keyboard() noexcept
{
    curr_state_ = state_0_;
    last_state_ = state_1_;
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

}

// �L�[�̉����C�x���g����
// 
// in Key : �������ꂽ�L�[�̃L�[�R�[�h( 1 ~255 )
//
//  �E�L�[�ɑΉ������r�b�g�������Ă���v�f�ԍ��̎擾
//      - Key / 8 �ŗv�f�ԍ��̎擾���s���Ă���B
//  �E�}�X�N�̍쐬
//      - 0b00000001 ~ 0b10000000 ���}�X�N�͈̔�
//      - 0x01���ő�7�r�b�g���փV�t�g����\��������B����7�Ƃ��������� % 8�ɂ�蓱���o�����
void Keyboard::keyDown( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << ((Key-1) % 8));
    
    curr_state_[elem] |= mask;
}

// �L�[�̗���C�x���g����
//
// in Key : ���コ�ꂽ�L�[�̃L�[�R�[�h( 1 ~ 255 )
void Keyboard::keyUp( uint8_t Key ) noexcept
{
    unsigned elem = static_cast<unsigned>( Key * ::kReciprocal8 );
    unsigned mask = (0b00000001 << ((Key-1) % 8));

    curr_state_[elem] &= ~mask;
}

// �V������Ԃ̎擾
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
        break;
        // TODO : �R���g���[���L�[�̃X�L�����R�[�h�𒲂ׂ�
        //        ���E�̓��͂ɑΉ�����
        //return toScancode
    case VK_MENU :
        break;
        // TODO : Alt�L�[�̍��E���͂ɑΉ�����
    }

    return 0;
}
} // unnamed namespace
// EOF
