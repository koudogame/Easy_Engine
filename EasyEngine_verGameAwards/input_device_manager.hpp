///
/// @file   input_device_manager.hpp
/// @author 板場
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
/// @brief   入力デバイスマネージャー
/// @details シングルトンクラスです。
///
class InputDeviceManager final :
    NonCopyable<InputDeviceManager>
{
public :
    ~InputDeviceManager();
    static std::unique_ptr<InputDeviceManager> create();

    ///
    /// @brief   デバイスへの接続
    /// @details 既に接続されている場合、接続されているデバイスを返却します。
    ///
    /// @tparam DeviceType : 接続する入力デバイス型
    ///
    /// @return 接続した入力デバイス
    ///
    template <class DeviceType>
    const DeviceType* connectDevice() noexcept { return connectDeviceImpl( Device<DeviceType>()); }

    ///
    /// @brief   入力デバイスの取得
    /// @details デバイスが接続されていない場合、nullptrを返却します。
    ///
    /// @tparam DeviceType : 取得する入力デバイス型
    ///
    /// @return 入力デバイス
    ///
    template <class DeviceType>
    const DeviceType* getDevice() noexcept { return getDeviceImpl( Device<DeviceType>() ); }

    ///
    /// @brief  入力イベント処理
    ///
    /// @param[in] Message : イベントメッセージ
    /// @param[in] wParam  : 追加のメッセージ情報
    /// @param[in] lParam  : 追加のメッセージ情報
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
