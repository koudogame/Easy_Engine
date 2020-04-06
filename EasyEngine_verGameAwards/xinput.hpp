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
/// @class   XInput
/// @brief   XInput�f�o�C�X
/// @details Singleton�N���X�ł��B�C���X�^���X���͋֎~���Ă��܂��B<br>
///          �C���X�^���X�ւ̃A�N�Z�X��instance�֐����g�p���ĉ������B
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

    ///< ���͏�Ԏ擾
    const State& getState() const noexcept { return state_; }

    XInput& operator=( const XInput& ) = default;

protected :
    FlagType newState( WORD, WORD, int ) noexcept;
    float stickNormalize( SHORT, int ) noexcept;

    State state_{};
    _XINPUT_STATE last_state_{};
};


template <DWORD UserIdx>
class XInputImpl :
    public XInput
{
public :
    XInputImpl() = default;
    void update() override;
};

using XInputP1 = XInputImpl<0U>;    ///< �Q�[���p�b�h 0
using XInputP2 = XInputImpl<1U>;    ///< �Q�[���p�b�h 1
using XInputP3 = XInputImpl<2U>;    ///< �Q�[���p�b�h 2
using XInputP4 = XInputImpl<3U>;    ///< �Q�[���p�b�h 3

END_EGEG
#endif /// !INCLUDED_EGEG_XINPUT_HEADER_
/// EOF
