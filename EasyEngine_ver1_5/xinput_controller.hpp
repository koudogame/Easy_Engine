///
/// @file   xinput_controller.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_

#include <type_traits>
#include <array>
#include <functional>
#include "controller.hpp"
#include "xinput.hpp"
#include "raw_number.hpp"

BEGIN_EGEG

///
/// @class   XInputController
/// @brief   XInput�f�o�C�X�p�R���g���[���[
/// @details �ێ�����f�o�C�X�ɕύX�������Ȃ����Ƃ�ۏ؂��܂��B
///
class XInputController :
    public Controller
{
public :
    using ButtonFunctionType  = std::function<void(InputDevice::InputType)>;
    using TriggerFunctionType = std::function<void(float)>;
    using StickFunctionType   = std::function<void(float, float)>;

    enum class Buttons : size_t
    {
        kDpadUp,
        kDpadDown,
        kDpadLeft,
        kDpadRight,
        kStart,
        kBack,
        kLeftThumb,
        kRightThumb,
        kLeftShoulder,
        kRightShoulder,
        kA,
        kB,
        kX,
        kY
    };

    enum class Triggers : size_t
    {
        kLeftTrigger,
        kRightTrigger
    };

    enum class Sticks : size_t
    {
        kLeftStick,
        kRightStick
    };

    ///
    /// @brief �R���X�g���N�^
    ///
    /// @param[in] Device : ���͂��擾����f�o�C�X
    ///
    XInputController( const XInput* Device ) noexcept;

    ///
    /// @brief �f�o�C�X�̃Z�b�g
    ///
    /// @param[in] Device : �Z�b�g����f�o�C�X
    ///
    void setDevice( const XInput* Device ) noexcept { device_ = Device; }
    ///
    /// @brief �f�o�C�X�擾
    ///
    /// @return �f�o�C�X
    ///
    const XInput* getDevice() const noexcept { return device_; }

    ///
    /// @brief   �{�^�����͂ɑ΂���֐��̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details �֐��̈����ɂ́A���͂̎�ނ�XInput::FlagType�œn���܂��B
    ///
    /// @param[in] Button   : �֐��ƕR�Â���{�^��
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class FunctionType>
    void registerFunction( Buttons Button, FunctionType&& Function ) { button_func_list_.at( rawNumber(Button) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   �{�^�����͂ɑ΂���֐��̒ǉ�( �����o�֐��p )
    /// @details �����_�pregisterFunction�Ɠ�����������܂��B
    ///
    /// @param[in] Button   : �֐��ƕR�Â���{�^��
    /// @param[in] Owner    : �֐����Ăяo���I�[�i�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class OwnerType>
    void registerFunction( Buttons Button, OwnerType* Owner, void(OwnerType::*Function)(InputDevice::InputType) ) { registerFunction( Button, std::bind(Function, Owner, std::placeholders::_1) ); }
    ///
    /// @brief  �{�^���Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Button : �R�Â�����������{�^��
    ///
    void unregisterFunction( Buttons Button ) { button_func_list_.at( rawNumber(Button) ) = nullptr; }

    ///
    /// @brief   �g���K�[���͂ɑ΂���֐��̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details �֐��̈����ɂ́A�g���K�[�̓��͒l(XInput�̒�߂�͈�)��n���܂��B
    ///
    /// @param[in] Trigger  : �֐��ƕR�Â���g���K�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class FunctionType>
    void registerFunction( Triggers Trigger, FunctionType Function ) { trigger_func_list_.at( rawNumber(Trigger) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   �g���K�[���͂ɑ΂���֐��̒ǉ�( �����o�֐��p )
    /// @details �����_�pregisterFunction�Ɠ�����������܂��B
    ///
    /// @param[in] Trigger  : �֐��ƕR�Â���g���K�[
    /// @param[in] Owner    : �֐����Ăяo���I�[�i�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class OwnerType>
    void registerFunction( Triggers Trigger, OwnerType* Owner, void(OwnerType::*Function)(float) ) { registerFunction( Trigger, std::bind(Function, Owner, std::placeholders::_1) ); }
    ///
    /// @brief  �g���K�[�Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Trigger : �R�Â�����������g���K�[
    ///
    void unregisterFunction( Triggers Trigger ) { trigger_func_list_.at( rawNumber(Trigger) ) = nullptr; }

    ///
    /// @brief   �X�e�B�b�N����(�����|��)�ɑ΂���֐��̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details �֐��̈����ɂ́A�X�e�B�b�N�̓��͒l(XInput�̒�߂�͈�)��n���܂��B <br>
    ///           ������ : �X�e�B�b�NX���̓��͒l <br>
    ///           ������ : �X�e�B�b�NY���̓��͒l
    ///
    /// @param[in] Stick    : �֐��ƕR�Â���X�e�B�b�N
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class FunctionType>
    void registerFunction( Sticks Stick, FunctionType&& Function ) { stick_func_list_.at( rawNumber(Stick) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   �X�e�B�b�N����(�����|��)�ɑ΂���֐��̒ǉ�( �����o�֐��p )
    /// @details �����_�pregisterFunction�Ɠ�����������܂��B
    ///
    /// @param[in] Stick    : �֐��ƕR�Â���X�e�B�b�N
    /// @param[in] Owner    : �֐����Ăяo���I�[�i�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class OwnerType>
    void registerFunction( Sticks Stick, OwnerType* Owner, void(OwnerType::*Function)(float, float) ) { registerFunction( Stick, std::bind(Function, Owner, std::placeholders::_1, std::placeholders::_2) ); }
    ///
    /// @brief  �X�e�B�b�N�Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Stick : �R�Â�����������X�e�B�b�N
    ///
    void unregisterFunction( Sticks Stick ) { stick_func_list_.at( rawNumber(Stick) ) = nullptr; }

// override
    void update() override;

private :
    const XInput* device_;
    std::array<ButtonFunctionType, 14U> button_func_list_;
    std::array<TriggerFunctionType, 2U> trigger_func_list_;
    std::array<StickFunctionType,   2U> stick_func_list_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
