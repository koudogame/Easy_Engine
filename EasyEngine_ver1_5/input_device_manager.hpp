///
/// @file   input_device_manager.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_INPUT_DEVICE_MANAGER_HEADER_
#define INCLUDED_EGEG_INPUT_DEVICE_MANAGER_HEADER_

#include <memory>
#include "non_copyable.hpp"
#include "task.hpp"
#include "xinput.hpp"
#include "keyboard.hpp"

BEGIN_EGEG

///
/// @class InputDeviceManager
/// @brief ���̓f�o�C�X�}�l�[�W���[
///
class InputDeviceManager final :
    NonCopyable<InputDeviceManager>
{
public :
    static std::unique_ptr<InputDeviceManager> create();
    ~InputDeviceManager();

    ///
    /// @brief   �f�o�C�X�ւ̐ڑ�
    /// @details ���ɐڑ�����Ă���ꍇ�A�ڑ�����Ă���f�o�C�X��ԋp���܂��B
    ///
    /// @tparam DeviceType : �ڑ�������̓f�o�C�X�^
    ///
    /// @return �ڑ��������̓f�o�C�X
    ///
    template <class DeviceType>
    const DeviceType* connectDevice() { return connectDeviceImpl( Device<DeviceType>{} ); }

    ///
    /// @brief   �f�o�C�X�Ƃ̐ڑ�������
    /// @details �ڑ�����Ă��Ȃ��ꍇ�́A�����s���܂���B
    ///
    /// @tparam DeviceType : �ڑ�������������̓f�o�C�X�^
    ///
    template <class DeviceType>
    void disConnectDevice() noexcept { disConnectDeviceImpl( Device<DeviceType>{} ); }

    ///
    /// @brief   ���̓f�o�C�X�̎擾
    /// @details �f�o�C�X���ڑ�����Ă��Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam DeviceType : �擾������̓f�o�C�X�^
    ///
    /// @return ���̓f�o�C�X
    ///
    template <class DeviceType>
    const DeviceType* getDevice() noexcept { return getDeviceImpl( Device<DeviceType>{} ); }

    ///
    /// @brief  ���̓C�x���g����
    ///
    /// @param[in] Message : �C�x���g���b�Z�[�W
    /// @param[in] wParam  : �ǉ��̃��b�Z�[�W���
    /// @param[in] lParam  : �ǉ��̃��b�Z�[�W���
    ///
    void eventProcessing( UINT Message, WPARAM wParam, LPARAM lParam ) const noexcept;

private :
    InputDeviceManager() = default;

    struct Keyboard_{};
    struct XInputP1_{};
    struct XInputP2_{};
    struct XInputP3_{};
    struct XInputP4_{};
    template <class DeviceType> struct Device;
    template <> struct Device<Keyboard> : Keyboard_{};
    template <> struct Device<XInputP1> : XInputP1_{};
    template <> struct Device<XInputP2> : XInputP2_{};
    template <> struct Device<XInputP3> : XInputP3_{};
    template <> struct Device<XInputP4> : XInputP4_{};

    void update( uint64_t );
    const Keyboard* connectDeviceImpl( Keyboard_ );
    const XInputP1* connectDeviceImpl( XInputP1_ );
    const XInputP2* connectDeviceImpl( XInputP2_ );
    const XInputP3* connectDeviceImpl( XInputP3_ );
    const XInputP4* connectDeviceImpl( XInputP4_ );
    void disConnectDeviceImpl( Keyboard_ ) noexcept { keyboard_.reset(); }
    void disConnectDeviceImpl( XInputP1_ ) noexcept { xinput_p1_.reset(); }
    void disConnectDeviceImpl( XInputP2_ ) noexcept { xinput_p2_.reset(); }
    void disConnectDeviceImpl( XInputP3_ ) noexcept { xinput_p3_.reset(); }
    void disConnectDeviceImpl( XInputP4_ ) noexcept { xinput_p4_.reset(); }
    const Keyboard* getDeviceImpl( Keyboard_ ) const noexcept { return keyboard_.get(); }
    const XInputP1* getDeviceImpl( XInputP1_ ) const noexcept { return xinput_p1_.get(); }
    const XInputP2* getDeviceImpl( XInputP2_ ) const noexcept { return xinput_p2_.get(); }
    const XInputP3* getDeviceImpl( XInputP3_ ) const noexcept { return xinput_p3_.get(); }
    const XInputP4* getDeviceImpl( XInputP4_ ) const noexcept { return xinput_p4_.get(); }

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
