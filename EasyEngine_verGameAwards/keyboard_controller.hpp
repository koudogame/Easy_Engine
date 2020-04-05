///
/// @file   keyboard_controller.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_KEYBOARD_CONTROLLER_HEADER_
#define INCLUDED_EGEG_KEYBOARD_CONTROLLER_HEADER_
#include <unordered_map>
#include <functional>
#include "controller.hpp"
#include "keyboard.hpp"

BEGIN_EGEG

///
/// @class   KeyboardController
/// @brief   �L�[�{�[�h�p�R���g���[���[
/// @details �ێ�����f�o�C�X�ɂ͕ύX�������Ȃ����Ƃ�ۏ؂��܂��B<br>
///          �Ăяo���֐���<br>
///           �߂�l��void ������InputDevice::FlagType�^�̊֐��ł��B<br>
///           �����ɂ͓��͂̏�Ԃ�n���܂��B
///
class KeyboardController :
    public Controller
{
public :
    using KeyType = uint8_t;
    ///
    /// @enum   Keys
    /// @brief  �L�[�̎�ޗ�
    ///
    enum class Keys : KeyType
    {
        kBackspace = 0x08,
        kTab,
        kEnter = 0x0D,
        kEscape = 0x1B,
        kSpace = 0x20,
        kLeft = 0x25,
        kUp,
        kRight,
        kDown,
        k0 = 0x30,
        k1,
        k2,
        k3,
        k4,
        k5,
        k6,
        k7,
        k8,
        k9,
        kA = 0x41,
        kB,
        kC,
        kD,
        kE,
        kF,
        kG,
        kH,
        kI,
        kJ,
        kK,
        kL,
        kM,
        kN,
        kO,
        kP,
        kQ,
        kR,
        kS,
        kT,
        kU,
        kV,
        kW,
        kX,
        kY,
        kZ,
        kNum0 = 0x60,
        kNum1,
        kNum2,
        kNum3,
        kNum4,
        kNum5,
        kNum6,
        kNum7,
        kNum8,
        kNum9,
        kF1 = 0x70,
        kF2,
        kF3,
        kF4,
        kF5,
        kF6,
        kF7,
        kF8,
        kF9,
        kF10,
        kF11,
        kF12,
        kLShift = 0xA0,
        kRShift,
        kLCtrl,
        kRCtrl,
        kLAlt,
        kRAlt,
        kColon = 0xBA,
        kSemiColon,
        kMinus,
        kPeriod,
        kSlash,
        kAtmark,
        kLSquareBracket = 0xDB,
        kBackSlash,
        kRSquareBracket,
        kCaret,
        kCapsLock = 0xF0,
    };

    ///< �R���X�g���N�^
    KeyboardController( const Keyboard* InputDevice ) noexcept;

    ///
    /// @brief   �L�[�ɑΉ����鏈���̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details ���ɏ������o�^����Ă���ꍇ�A�㏑�����܂��B
    ///
    /// @param[in] Key      : �����ƕR�Â���L�[
    /// @param[in] Function : �L�[�ɕR�Â��鏈��
    ///
    void registerFunction( Keys Key, void(*Function)(InputDevice::FlagType) )
    {
        function_list_[enumToValue(Key)] = Function;
    }
    ///
    /// @brief   �L�[�ɑΉ����鏈���̒ǉ�( �����o�֐��p )
    /// @details �����_�pregisterFunction�Ɠ�����������܂��B
    ///
    /// @param[in] Key      : �����ƕR�Â���L�[
    /// @param[in] Owner    : �������Ăяo���I�[�i�[
    /// @param[in] Function : �L�[�ɕR�Â��鏈��
    ///
    template <class OwnerType>
    void registerFunction( Keys Key, OwnerType* Owner, void(OwnerType::*Function)(InputDevice::FlagType) )
    {
        registerFunction( Key, std::bind(Function, Owner, std::placeholders::_1) );
    }

    ///
    /// @brief   �L�[�ɑΉ����鏈���̍폜
    /// @details �����̃L�[�ɑΉ����������������ꍇ�A�����s���܂���B<br>
    ///          registerFunction( Key, nullptr )�Ƃ����ꍇ�Ɠ��삪�قȂ�܂��B
    ///
    /// @param[in] Key : �폜���鏈���ɑΉ������L�[
    ///
    void unregisterFunction( Keys key );
    
/*-----------------------------------------------------------------*/
// Controller
    void update() override;
/*-----------------------------------------------------------------*/

private :
    const Keyboard* device_;
    std::unordered_map<KeyType ,std::function<void(InputDevice::FlagType)>> function_list_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_KEYBOARD_CONTROLLER_HEADER_
/// EOF
