// �쐬�� : ��
#include "keyboard_controller.hpp"
#include "utility_function.hpp"

BEGIN_EGEG

namespace
{
    using CtrlerType = KeyboardController;
    constexpr CtrlerType::KeyType kVKStart = 0x08;
    constexpr CtrlerType::KeyType KVKLast  = enumToValue(CtrlerType::Keys::kCapsLock);
} // unnamed namespace

// KeyboardController �֐���`
/*===========================================================================*/
// �R���X�g���N�^
KeyboardController::KeyboardController( const Keyboard* Device ) noexcept :
    device_( Device )
{
}

// �����̍폜
void KeyboardController::unregisterFunction( KeyboardController::Keys Key )
{
    auto find = function_list_.find( enumToValue(Key) );
    if( find != function_list_.end() )
    { // �폜�Ώۂ̊֐�������ꍇ
        find->second = nullptr;
    }
}

// �X�V����
void KeyboardController::update()
{
    for( KeyType vk = kVKStart; vk <= KVKLast; ++vk )
    { // �L�[�ɑΉ������֐����Ăяo��
        auto find = function_list_.find( vk );
        if( find != function_list_.end() )
        { // �Ή������֐�������ꍇ
            find->second(
                *(reinterpret_cast<const InputDevice::FlagType*>(&device_->getState()) +
                vk)
            );
        }
    }
}

END_EGEG
// EOF
