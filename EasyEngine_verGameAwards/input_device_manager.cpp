// 作成者 : 板場
#include "input_device_manager.hpp"
#ifdef _DEBUG
#include <cassert>
#endif
#include "easy_engine.hpp"

BEGIN_EGEG

// InputDeviceManager 関数定義
/*===========================================================================*/
// コンストラクタ
InputDeviceManager::InputDeviceManager()
{
}

// デストラクタ
InputDeviceManager::~InputDeviceManager()
{
}

// 生成
std::unique_ptr<InputDeviceManager> InputDeviceManager::create()
{
#ifdef _DEBUG
    static unsigned created_cnt;
    assert( !created_cnt++ && "InputDeviceManagerはシングルトンクラスです。" );
#endif
    std::unique_ptr<InputDeviceManager> created( new InputDeviceManager() );

    // タスクの登録
    created->task_.setJob( created.get() , &InputDeviceManager::update );
    EasyEngine::getTaskManager()->registerJob( &created->task_, 0U );

    return created;
}

// イベント処理
void InputDeviceManager::inputEventProcessing( UINT Msg, WPARAM wPrm, LPARAM lPrm ) noexcept
{
    if( keyboard_ ) keyboard_->eventProcessing( Msg, wPrm, lPrm );
}

// 更新
void InputDeviceManager::update( uint64_t )
{
    // nullptrチェックを行う、安全な更新
    auto updateDevice = []( InputDevice* Device )
    {
        if( Device )
        {
            Device->update();
        }
    };
    updateDevice( keyboard_.get() );
    updateDevice( xinput_p1_.get() );
    updateDevice( xinput_p2_.get() );
    updateDevice( xinput_p3_.get() );
    updateDevice( xinput_p4_.get() );
}

// キーボードと接続
const Keyboard* InputDeviceManager::connectDeviceImpl( Keyboard_ )
{
    if( !keyboard_ ) keyboard_ = std::make_unique<Keyboard>();
    return keyboard_.get();
}
// キーボードの取得
const Keyboard* InputDeviceManager::getDeviceImpl( Keyboard_ ) noexcept
{
    return keyboard_.get();
}

// XInputP1ゲームパッドと接続
const XInputP1* InputDeviceManager::connectDeviceImpl( XInputP1_ )
{
    if( !xinput_p1_ ) xinput_p1_ = std::make_unique<XInputP1>();
    return xinput_p1_.get();
}
// XInputP1ゲームパッドの取得
const XInputP1* InputDeviceManager::getDeviceImpl( XInputP1_ ) noexcept
{
    return xinput_p1_.get();
}

// XInputP2ゲームパッドと接続
const XInputP2* InputDeviceManager::connectDeviceImpl( XInputP2_ )
{
    if( !xinput_p2_ ) xinput_p2_ = std::make_unique<XInputP2>();
    return xinput_p2_.get();
}
// XInputP2ゲームパッドの取得
const XInputP2* InputDeviceManager::getDeviceImpl( XInputP2_ ) noexcept
{
    return xinput_p2_.get();
}

// XInputP3ゲームパッドと接続
const XInputP3* InputDeviceManager::connectDeviceImpl( XInputP3_ )
{
    if( !xinput_p3_ ) xinput_p3_ = std::make_unique<XInputP3>();
    return xinput_p3_.get();
}
// XInputP3ゲームパッドの取得
const XInputP3* InputDeviceManager::getDeviceImpl( XInputP3_ ) noexcept
{
    return xinput_p3_.get();
}

// XInputP4ゲームパッドと接続
const XInputP4* InputDeviceManager::connectDeviceImpl( XInputP4_ )
{
    if( !xinput_p4_ ) xinput_p4_ = std::make_unique<XInputP4>();
    return xinput_p4_.get();
}
// XInputP4ゲームパッドの取得
const XInputP4* InputDeviceManager::getDeviceImpl( XInputP4_ ) noexcept
{
    return xinput_p4_.get();
}

END_EGEG
// EOF
