///
/// @file   xinput_controller.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
#include <array>
#include "controller.hpp"
#include "xinput.hpp"
BEGIN_EGEG
///
/// @class  XInputController
/// @brief  XInput�p�R���g���[���[
///
class XInputController :
    public Controller
{
public :
    template <class Elem, size_t Size>
    using FunctionList = std::array<Elem, Size>;
    using ButtonsFunctionType = void(*)( XInput::FlagType );
    using TriggersFunctionType = void(*)( float );
    using SticksFunctionType   = void(*)( float, float );

    ///
    /// @enum   Buttons
    /// @brief  �{�^���̎�ޗ�
    ///
    enum Buttons : size_t
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
    enum Triggers : size_t
    {
        kLeftTrigger,
        kRightTrigger
    };
    ///
    /// @enum   Sticks
    /// @brief  �X�e�B�b�N�̎�ޗ�
    ///
    enum Sticks : size_t
    {
        kLeftStick,
        kRightStick
    };

    ///< �R���X�g���N�^
    XInputController( const XInput* InputDevice = nullptr ) noexcept;

    ///
    /// @brief   �{�^�����͂ɑ΂���֐��̒ǉ�
    /// @details �֐��̈����ɂ́A���͂̎�ނ�XInput::FlagType�œn���܂��B
    ///
    /// @param[in] Button   ; �֐��ƕR�Â���{�^��
    /// @param[in] Function : �Ăяo���֐�
    ///
    void registerFunction( Buttons Button, ButtonsFunctionType Function ) { buttons_func_.at( Button ) = Function; }
    ///
    /// @brief  �{�^���Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Button : �R�Â�����������{�^��
    ///
    void unregisterFunction( Buttons Button ) { buttons_func_.at( Button ) = nullptr; }
    ///
    /// @brief   �g���K�[���͂ɑ΂���֐��̒ǉ�
    /// @details �֐��̈����ɂ́A�g���K�[�̓��͒l(XInput�̒�߂�͈�)��n���܂��B
    ///
    /// @param[in] Trigger  : �֐��ƕR�Â���g���K�[
    /// @param[in] Function : �Ăяo���֐�
    ///
    void registerFunction( Triggers Trigger, TriggersFunctionType Function ) { triggers_func_.at( Trigger ) = Function; }
    ///
    /// @brief  �g���K�[�Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Trigger : �R�Â�����������g���K�[
    ///
    void unregisterFunction( Triggers Trigger ) { triggers_func_.at( Trigger ) = nullptr; }
    ///
    /// @brief   �X�e�B�b�N����(�����|��)�ɑ΂���֐��̒ǉ�
    /// @details �֐��̈����ɂ́A�X�e�B�b�N�̓��͒l(XInput�̒�߂�͈�)��n���܂��B<br>
    ///          ������ : �X�e�B�b�NX���̓��͒l<br>
    ///          ������ : �X�e�B�b�NY���̓��͒l
    ///
    /// @param[in] Stick    : �֐��ƕR�Â���X�e�B�b�N
    /// @param[in] Function : �Ăяo���֐�
    ///
    void registerFunction( Sticks Stick, SticksFunctionType Function ) { sticks_func_.at( Stick ) = Function; }
    ///
    /// @brief  �X�e�B�b�N�Ɗ֐��̕R�Â�������
    ///
    /// @param[in] Stick : �R�Â�����������X�e�B�b�N
    ///
    void unregisterFunction( Sticks Stick ) { sticks_func_.at( Stick ) = nullptr; }
    
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
    const XInput* getDevice() const noexcept { return device_; }
        
/*-----------------------------------------------------------------*/
// Controller
    void update() override;
/*-----------------------------------------------------------------*/

private :
    ///
    /// @param[in] CallFunction : �Ăяo���֐��Q
    /// @param[in] Args : �Ăяo���֐��ɓn���������X�g
    ///
    template <class FuncType, class ...Ts>
    inline void callFuncSafe( FuncType CallFunction, Ts... Args )
    {   // ���S�Ȋ֐��Ăяo��
        if( CallFunction ) CallFunction( Args... );
    }

    FunctionList<ButtonsFunctionType, 14U> buttons_func_;
    FunctionList<TriggersFunctionType, 2U> triggers_func_;
    FunctionList<SticksFunctionType, 2U> sticks_func_;
    const XInput* device_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_CONTROLLER_HEADER_
/// EOF
