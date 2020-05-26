// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "input_device_manager.hpp"
#ifdef _DEBUG
#include <cassert>
#endif
#include "engine.hpp"


BEGIN_EGEG

/******************************************************************************

	InputDeviceManager

******************************************************************************/
 // ��������
std::unique_ptr<InputDeviceManager> InputDeviceManager::create()
{
#ifdef _DEBUG
    static unsigned created_cnt;
    assert( !created_cnt++ && "InputDeviceManager�𕡐��쐬���邱�Ƃ͂ł��܂���B" );
#endif
    auto created = std::unique_ptr<InputDeviceManager>{ new InputDeviceManager{} };
    created->task_.setJob( created.get(), &InputDeviceManager::update );
    EasyEngine::getTaskManager()->registerJob( &created->task_ );

    return created;
}


 // �f�X�g���N�^
InputDeviceManager::~InputDeviceManager() = default;


 // �C�x���g����
void InputDeviceManager::eventProcessing( UINT Message, WPARAM wParam, LPARAM lParam ) const noexcept
{
    if( keyboard_ ) keyboard_->eventProcessing( Message, wParam, lParam );
}


 // �X�V����
void InputDeviceManager::update( uint64_t )
{
    auto safeUpdate = [this]( InputDevice* Device )
    {
        if( Device ) Device->update();
    };

    safeUpdate( keyboard_.get() );
    safeUpdate( xinput_p1_.get() );
    safeUpdate( xinput_p2_.get() );
    safeUpdate( xinput_p3_.get() );
    safeUpdate( xinput_p4_.get() );
}


 // �L�[�{�[�h�Ɛڑ�
const Keyboard* InputDeviceManager::connectDeviceImpl( Keyboard_ )
{
    if( !keyboard_ ) keyboard_ = std::make_unique<Keyboard>();
    return keyboard_.get();
}


 // XInputP1�Ɛڑ�
const XInputP1* InputDeviceManager::connectDeviceImpl( XInputP1_ )
{
    if( !xinput_p1_ ) xinput_p1_ = std::make_unique<XInputP1>();
    return xinput_p1_.get();
}

 // XInputP2�Ɛڑ�
const XInputP2* InputDeviceManager::connectDeviceImpl(XInputP2_)
{
    if( !xinput_p2_ ) xinput_p2_ = std::make_unique<XInputP2>();
    return xinput_p2_.get();
}


 // XInputP3�Ɛڑ�
const XInputP3* InputDeviceManager::connectDeviceImpl(XInputP3_)
{
    if( !xinput_p3_ ) xinput_p3_ = std::make_unique<XInputP3>();
    return xinput_p3_.get();
}


 // XInputP4�Ɛڑ�
const XInputP4* InputDeviceManager::connectDeviceImpl(XInputP4_)
{
    if( !xinput_p4_ ) xinput_p4_ = std::make_unique<XInputP4>();
    return xinput_p4_.get();
}

END_EGEG
// EOF
