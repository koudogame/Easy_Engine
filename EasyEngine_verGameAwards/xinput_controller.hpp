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
#include "utility_function.hpp"

BEGIN_EGEG

///
/// @class   XInputController
/// @brief   XInput�p�R���g���[���[
/// @details �ێ�����f�o�C�X�ɕύX�������Ȃ����Ƃ�ۏ؂��܂��B
///
class XInputController :
    public Controller
{
public :
    using ButtonsFunctionType  = std::function<void(InputDevice::FlagType)>;
    using TriggersFunctionType = std::function<void(float)>;
    using SticksFunctionType   = std::function<void(float, float)>;

    ///
    /// @enum   Buttons
    /// @brief  �{�^���̎�ޗ�
    ///
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
    ///
    /// @enum   Triggers
    /// @brief  �g���K�[�̎�ޗ�
    ///
    enum class Triggers : size_t
    {
        kLeftTrigger,
        kRightTrigger
    };
    ///
    /// @enum   Sticks
    /// @brief  �X�e�B�b�N�̎�ޗ�
    ///
    enum class Sticks : size_t
    {
        kLeftStick,
        kRightStick
    };

    ///< �R���X�g���N�^
    XInputController( const XInput* InputDevice ) noexcept;

    ///
    /// @brief   �{�^�����͂ɑ΂���֐��̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details �֐��̈����ɂ́A���͂̎�ނ�XInput::FlagType�œn���܂��B
    ///
    /// @param[in] Button   : �֐��ƕR�Â���{�^��
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class FunctionType>
    void registerFunction( Buttons Button, FunctionType&& Function ) { button_func_list_.at( enumToValue(Button) ) = std::forward<FunctionType>(Function); }
    ///
    /// @brief   �{�^�����͂ɑ΂���֐��̒ǉ�( �����o�֐��p )
    /// @details �����_�pregisterFunction�Ɠ�����������܂��B
    ///
    /// @param[in] Button   : �֐��ƕR�Â���{�^��
    /// @param[in] Owner    : �֐����Ăяo���I�[�i�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class OwnerType>
    void registerFunction( Buttons Button, OwnerType* Owner, void(OwnerType::*Function)(InputDevice::FlagType) ) { registerFunction( Button, std::bind(Function, Owner, std::placeholders::_1) ); }
    ///
    /// @brief  �{�^���Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Button : �R�Â�����������{�^��
    ///
    void unregisterFunction( Buttons Button ) { button_func_list_.at( enumToValue(Button) ) = nullptr; }
    ///
    /// @brief   �g���K�[���͂ɑ΂���֐��̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details �֐��̈����ɂ́A�g���K�[�̓��͒l(XInput�̒�߂�͈�)��n���܂��B
    ///
    /// @param[in] Trigger  : �֐��ƕR�Â���g���K�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class FunctionType>
    void registerFunction( Triggers Trigger, FunctionType&& Function ) { trigger_func_list_.at( enumToValue(Trigger) ) = std::forward<FunctionType>(Function); }
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
    void unregisterFunction( Triggers Trigger ) { trigger_func_list_.at( enumToValue(Trigger) ) = nullptr; }
    ///
    /// @brief   �X�e�B�b�N����(�����|��)�ɑ΂���֐��̒ǉ�( �����_���A�񃁃��o�֐��p )
    /// @details �֐��̈����ɂ́A�X�e�B�b�N�̓��͒l(XInput�̒�߂�͈�)��n���܂��B<br>
    ///          ������ : �X�e�B�b�NX���̓��͒l<br>
    ///          ������ : �X�e�B�b�NY���̓��͒l
    ///
    /// @param[in] Stick    : �֐��ƕR�Â���X�e�B�b�N
    /// @param[in] Function : �Ăяo���֐�
    ///
    template <class FunctionType>
    void registerFunction( Sticks Stick, FunctionType&& Function ) { stick_func_list_.at( enumToValue(Stick) ) = std::forward<FunctionType>(Function); }
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
    void unregisterFunction( Sticks Stick ) { stick_func_list_.at( enumToValue(Stick) ) = nullptr; }
    
    ///
    /// @brief  ���̓f�o�C�X�̐ݒ�
    ///
    /// @param[in] XInputDevice : �ݒ肷��f�o�C�X
    ///
    void setDevice( const XInput* XInputDevice ) noexcept { device_ = XInputDevice; }
    ///
    /// @brief  ���̓f�o�C�X�̎擾
    ///
    /// @return ���̓f�o�C�X
    ///
    const XInput& getDevice() const noexcept { return *device_; }
        
/*-----------------------------------------------------------------*/
// Controller
    void update() override;
/*-----------------------------------------------------------------*/

private :
    ///
    /// @param[in] Functions : �Ăяo���֐��Q
    /// @param[in] Index     : �Ăяo���֐����w�肷��C���f�b�N�X
    /// @param[in] Args      : �Ăяo���֐��ɓn���������X�g
    ///
    template <class FuncList, class EnumType, class ...Ts>
    void callFuncSafe( FuncList& Functions, EnumType Index, Ts&& ...Args )
    {   // ���S�Ȋ֐��Ăяo��
        if( auto func = Functions.at(enumToValue(Index)) ) func( std::forward<Ts>(Args)... );
    }

    const XInput* device_;
    std::array<ButtonsFunctionType, 14U> button_func_list_;
    std::array<TriggersFunctionType, 2U> trigger_func_list_;
    std::array<SticksFunctionType, 2U>   stick_func_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
