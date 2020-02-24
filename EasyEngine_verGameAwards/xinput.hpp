///
/// @file   xinput.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_XINPUT_HEADER_
#define INCLUDED_EGEG_XINPUT_HEADER_
#include <Windows.h> ///< target platform
#include <Xinput.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  XInput
/// @brief  XInput�f�o�C�X�̊��N���X
///
class XInput
{
public :
    using FlagType = unsigned char;

    ///< ���͏�Ԕ���t���O
    enum InputState : FlagType
    {
        kNone     = 0U,     ///< ���͂Ȃ�
        kInput    = 0b001,  ///< ���͂���
        kPressed  = 0b011,  ///< ���͂���(�����ꂽ�u��)
        kReleased = 0b100,  ///< ���͂Ȃ�(�����ꂽ�u��)
    };

    ///< ���͏�Ԋi�[�\����
    struct State
    {
        bool connected; ///< true : �ڑ��@false : �ڑ��Ȃ�

        FlagType dpad_up;
        FlagType dpad_down;
        FlagType dpad_left;
        FlagType dpad_right;
        FlagType start;
        FlagType back;
        FlagType left_thumbstick;
        FlagType right_thumbstick;
        FlagType left_shoulder;
        FlagType right_shoulder;
        FlagType a;
        FlagType b;
        FlagType x;
        FlagType y;

        float left_trigger;         ///< 0.0F ~ 1.0F �͈̔�
        float right_trigger;        ///< 0.0F ~ 1.0F �͈̔�

        float left_thumbstick_x;    ///< 0.0F ~ 1.0F �͈̔�
        float left_thumbstick_y;    ///< 0.0F ~ 1.0F �͈̔�
        float right_thumbstick_x;   ///< 0.0F ~ 1.0F �͈̔�
        float right_thumbstick_y;   ///< 0.0F ~ 1.0F �͈̔�
    };

    ///
    /// @brief   �R���X�g���N�^
    /// @details �R���g���[���[�̃C���f�b�N�X��[0 ~ 3]�͈̔͂Ŏw�肵�ĉ������B
    ///
    /// @param[in] UserIndex : �R���g���[���[�̃C���f�b�N�X
    ///
    XInput( DWORD UserIndex ) noexcept;

    ///< ���͏�ԍX�V
    void update() noexcept;

    ///< ���͏�Ԏ擾
    const State& getState() const noexcept { return state_; }

    
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

private :
    FlagType newState( WORD, WORD, int ) noexcept;
    float stickNormalize( SHORT, int ) noexcept;

    DWORD user_idx_;
    State state_{};
    _XINPUT_STATE last_state_{};
};
END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_HEADER_
/// EOF
