///
/// @file   input_device.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_INPUT_DEVICE_HEADER_
#define INCLUDED_EGEG_INPUT_DEVICE_HEADER_

#include <cstdint>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class InputDevice
/// @brief ���̓f�o�C�X���N���X
///
class InputDevice
{
public :
    using InputType = uint8_t;

    enum InputState : InputType
    {
        kNone     = 0b000, ///< ���͂Ȃ�
        kInput    = 0b001, ///< ���͂���
        kPressed  = 0b010, ///< ���͂���( �����ꂽ�u�� )
        kReleased = 0b100  ///< ���͂Ȃ�( �����ꂽ�u�� )
    };

    virtual ~InputDevice() = default;

    ///
    /// @brief ���͏�Ԃ̍X�V
    ///
    virtual void update() = 0;

    ///
    /// @brief ���͂����邩�m�F
    ///
    /// @param[in] State : ���肷����
    ///
    /// @return true : ����@false : �Ȃ�
    ///
    static bool isInput( InputType State ) noexcept { return State & kInput; }
    ///
    /// @brief ���͂��������u�Ԃ��m�F
    ///
    /// @param[in] State : ���肷����
    ///
    /// @return true : �����@false : �����łȂ�
    ///
    static bool isPressed( InputType State ) noexcept { return State & kPressed; }
    ///
    /// @brief ���͂��p������Ă��邩�m�F
    ///
    /// @param[in] State : ���肷����
    ///
    /// @return true : �����@false : �����łȂ�
    ///
    static bool isHold( InputType State ) noexcept { return State == kInput; }
    ///
    /// @brief ���͂������Ȃ����u�Ԃ��m�F
    ///
    /// @param[in] State : ���肷����
    ///
    /// @return true : �����@false : �����łȂ�
    ///
    static bool isReleased( InputType State ) noexcept { return State & kReleased; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_INPUT_DEVICE_HEADER_
/// EOF
