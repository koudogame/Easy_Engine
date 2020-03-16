///
/// @file   xinput_controller.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#include <array>
#include <type_traits>
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
    using DeviceType = const XInput;

    using ButtonsFunctionType  = void(*)( InputDevice::FlagType );
    using TriggersFunctionType = void(*)( float );
    using SticksFunctionType   = void(*)( float, float );

    template <class Elem, size_t Size>
    using FunctionList = std::array<Elem, Size>;


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
    XInputController( DeviceType& InputDevice ) noexcept;

    ///
    /// @brief   �{�^�����͂ɑ΂���֐��̒ǉ�
    /// @details �֐��̈����ɂ́A���͂̎�ނ�XInput::FlagType�œn���܂��B
    ///
    /// @param[in] Button   ; �֐��ƕR�Â���{�^��
    /// @param[in] Function : �Ăяo���֐�
    ///
    void registerFunction( Buttons Button, ButtonsFunctionType Function ) { buttons_func_.at( EnumToValue(Button) ) = Function; }
    ///
    /// @brief  �{�^���Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Button : �R�Â�����������{�^��
    ///
    void unregisterFunction( Buttons Button ) { buttons_func_.at( EnumToValue(Button) ) = nullptr; }
    ///
    /// @brief   �g���K�[���͂ɑ΂���֐��̒ǉ�
    /// @details �֐��̈����ɂ́A�g���K�[�̓��͒l(XInput�̒�߂�͈�)��n���܂��B
    ///
    /// @param[in] Trigger  : �֐��ƕR�Â���g���K�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    void registerFunction( Triggers Trigger, TriggersFunctionType Function ) { triggers_func_.at( EnumToValue(Trigger) ) = Function; }
    ///
    /// @brief  �g���K�[�Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Trigger : �R�Â�����������g���K�[
    ///
    void unregisterFunction( Triggers Trigger ) { triggers_func_.at( EnumToValue(Trigger) ) = nullptr; }
    ///
    /// @brief   �X�e�B�b�N����(�����|��)�ɑ΂���֐��̒ǉ�
    /// @details �֐��̈����ɂ́A�X�e�B�b�N�̓��͒l(XInput�̒�߂�͈�)��n���܂��B<br>
    ///          ������ : �X�e�B�b�NX���̓��͒l<br>
    ///          ������ : �X�e�B�b�NY���̓��͒l
    ///
    /// @param[in] Stick    : �֐��ƕR�Â���X�e�B�b�N
    /// @param[in] Function : �Ăяo���֐�
    ///
    void registerFunction( Sticks Stick, SticksFunctionType Function ) { sticks_func_.at( EnumToValue(Stick) ) = Function; }
    ///
    /// @brief  �X�e�B�b�N�Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Stick : �R�Â�����������X�e�B�b�N
    ///
    void unregisterFunction( Sticks Stick ) { sticks_func_.at( EnumToValue(Stick) ) = nullptr; }
    
    ///
    /// @brief  ���̓f�o�C�X�̐ݒ�
    ///
    /// @param[in] XInputDevice : �ݒ肷��f�o�C�X
    ///
    void setDevice( DeviceType& XInputDevice ) noexcept { device_ = &XInputDevice; }
    ///
    /// @brief  ���̓f�o�C�X�̎擾
    ///
    /// @return ���̓f�o�C�X
    ///
    DeviceType& getDevice() const noexcept { return *device_; }
        
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
    inline void callFuncSafe( FuncList& Functions, EnumType Index, Ts&& ...Args )
    {   // ���S�Ȋ֐��Ăяo��
        if( auto func = Functions.at(EnumToValue(Index)) ) func( std::forward<Ts>(Args)... );
    }

    DeviceType* device_;
    FunctionList<ButtonsFunctionType, 14U> buttons_func_;
    FunctionList<TriggersFunctionType, 2U> triggers_func_;
    FunctionList<SticksFunctionType, 2U> sticks_func_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
