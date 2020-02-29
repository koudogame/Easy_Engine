///
/// @file   xinput.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_XINPUT_HEADER_
#define INCLUDED_EGEG_XINPUT_HEADER_
#include <Windows.h> ///< target platform
#include <Xinput.h>
#include "input_device.hpp"
BEGIN_EGEG
///
/// @class  XInput
/// @brief  XInput�f�o�C�X
///
class XInput :
    public InputDevice
{
public :
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

    ///< ���͏�Ԏ擾
    const State& getState() const noexcept { return state_; }

        
/*-----------------------------------------------------------------*/
// InputDevice
    ///< ���͏�ԍX�V
    void update() override;
/*-----------------------------------------------------------------*/

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
