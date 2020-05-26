// �쐬�� : ��
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
 // �R���X�g���N�^
KeyboardController::KeyboardController( const Keyboard* Device ) noexcept :
    device_{ Device }
{
}


 // �֐��̓o�^����
void KeyboardController::unregisterFunction( Keys Key )
{
    auto find = function_list_.find( rawNumber(Key) );
    if( find != function_list_.end() )
    {
        find->second = nullptr;
    }
}


 // �X�V
void KeyboardController::update()
{
    for( KeyType vk = kStartKey; vk <= kLastKey; ++vk )
    {
        auto find = function_list_.find( vk );
        if( find != function_list_.end() )
        { // �L�[�ɑΉ������֐�������ꍇ�ɌĂяo��
            find->second(
                *(reinterpret_cast<const InputDevice::InputType*>(&device_->getState()) +
                vk)
            );
        }
    }
}

END_EGEG
/// EOF
