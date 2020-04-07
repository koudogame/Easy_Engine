///
/// @file   input_device_manager.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_INPUT_DEVICE_MANAGER_HEADER_
#define INCLUDED_EGEG_INPUT_DEVICE_MANAGER_HEADER_

#include <memory>
#include "noncopyable.hpp"
#include "input_device.hpp"
#include "xinput.hpp"
#include "keyboard.hpp"
#include "task.hpp"

BEGIN_EGEG

///
/// @class   InputDeviceManager
/// @brief   ���̓f�o�C�X�}�l�[�W���[
/// @details �V���O���g���N���X�ł��B
///
class InputDeviceManager final :
    NonCopyable<InputDeviceManager>
{
public :
    ~InputDeviceManager();
    static std::unique_ptr<InputDeviceManager> create();

    ///
    /// @brief   �f�o�C�X�ւ̐ڑ�
    /// @details ���ɐڑ�����Ă���ꍇ�A�ڑ�����Ă���f�o�C�X��ԋp���܂��B
    ///
    /// @tparam DeviceType : �ڑ�������̓f�o�C�X�^
    ///
    /// @return �ڑ��������̓f�o�C�X
    ///
    template <class DeviceType>
    const DeviceType* connectDevice() noexcept { return connectDeviceImpl( Device<DeviceType>()); }

    ///
    /// @brief   ���̓f�o�C�X�̎擾
    /// @details �f�o�C�X���ڑ�����Ă��Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam DeviceType : �擾������̓f�o�C�X�^
    ///
    /// @return ���̓f�o�C�X
    ///
    template <class DeviceType>
    const DeviceType* getDevice() noexcept { return getDeviceImpl( Device<DeviceType>() ); }

    ///
    /// @brief  ���̓C�x���g����
    ///
    /// @param[in] Message : �C�x���g���b�Z�[�W
    /// @param[in] wParam  : �ǉ��̃��b�Z�[�W���
    /// @param[in] lParam  : �ǉ��̃��b�Z�[�W���
    ///
    void inputEventProcessing( UINT Message, WPARAM wParam, LPARAM lParam ) noexcept;

private :
    struct keyboard{};
    struct xinputp1{};
    struct xinputp2{};
    struct xinputp3{};
    struct xinputp4{};
    template <class DeviceType>
    struct Device;
    template <>
    struct Device<Keyboard> : keyboard {};
    template <>
    struct Device<XInputP1> : xinputp1 {};
    template <>
    struct Device<XInputP2> : xinputp2 {};
    template <>
    struct Device<XInputP3> : xinputp3 {};
    template <>
    struct Device<XInputP4> : xinputp4 {};
    
    InputDeviceManager();

    void update( uint64_t );
    const Keyboard* connectDeviceImpl( keyboard );
    const XInputP1* connectDeviceImpl( xinputp1 );
    const XInputP2* connectDeviceImpl( xinputp2 );
    const XInputP3* connectDeviceImpl( xinputp3 );
    const XInputP4* connectDeviceImpl( xinputp4 );
    const Keyboard* getDeviceImpl( keyboard ) noexcept;
    const XInputP1* getDeviceImpl( xinputp1 ) noexcept;
    const XInputP2* getDeviceImpl( xinputp2 ) noexcept;
    const XInputP3* getDeviceImpl( xinputp3 ) noexcept;
    const XInputP4* getDeviceImpl( xinputp4 ) noexcept;

    Task task_;
    std::unique_ptr<Keyboard> keyboard_;
    std::unique_ptr<XInputP1> xinput_p1_;
    std::unique_ptr<XInputP2> xinput_p2_;
    std::unique_ptr<XInputP3> xinput_p3_;
    std::unique_ptr<XInputP4> xinput_p4_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_INPUT_DEVICE_MANAGER_HEADER_
/// EOF
