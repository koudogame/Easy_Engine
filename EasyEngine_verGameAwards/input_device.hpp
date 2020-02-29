///
/// @file   input_device.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_INPUT_DEVICE_HEADER_
#define INCLUDED_EGEG_INPUT_DEVICE_HEADER_
#include "egeg.hpp"
///
/// @class  InputDevice
/// @brief  ���͎擾�֌W�̊��N���X
///
class InputDevice
{
public :
    using FlagType = unsigned char;

    ///< ���͏�Ԕ���t���O
    enum InputState : FlagType
    {
        kNone     = 0U,     ///< ���͂Ȃ�
        kInput    = 0b001,  ///< ���͂���
        kPressed  = 0b010,  ///< ���͂���(�����ꂽ�u��)
        kReleased = 0b100,  ///< ���͂Ȃ�(�����ꂽ�u��)
    };

    ///
    /// @brief  ���͏�Ԃ̍X�V����
    ///
    virtual void update() = 0;

    ///
    /// @brief  �{�^����������Ă��邩����
    ///
    /// @param[in] ButtonState : ���肷��{�^���̏��
    ///
    /// @return ������Ă���[ true ]�@������Ă��Ȃ�[ false ]
    ///
    static bool isInput( FlagType ButtonState ) noexcept { return ButtonState & InputState::kInput; }
    ///
    /// @brief  �{�^���������ꂽ�u�Ԃ�����
    ///
    /// @param[in] ButtonState : ���肷��{�^���̏��
    ///
    /// @return �����ꂽ�u��[ true ]�@�����ꂽ�u�Ԃł͂Ȃ�[ false ]
    ///
    static bool isPressed( FlagType ButtonState ) noexcept { return ButtonState & InputState::kPressed; }
    ///
    /// @brief  �{�^�����p�����ĉ�����Ă��邩����
    ///
    /// @param[in] ButtonState : ���肷��{�^���̏��
    ///
    /// @return �p�����ĉ�����Ă���[ true ]�@�p�����ĉ�����Ă��Ȃ�[ false ]
    ///
    static bool isHold( FlagType ButtonState ) noexcept { return ButtonState == InputState::kInput; }
    ///
    /// @brief  �{�^���������ꂽ�u�Ԃ�����
    ///
    /// @param[in] ButtonState : ���肷��{�^���̏��
    ///
    /// @return �����ꂽ�u��[ true ]�@�����ꂽ�u�Ԃł͂Ȃ�[ false ]
    ///
    static bool isReleased( FlagType ButtonState ) noexcept { return ButtonState & InputState::kReleased; }
};
#endif /// !INCLUDED_EGEG_INPUT_DEVICE_HEADER_
/// EOF
