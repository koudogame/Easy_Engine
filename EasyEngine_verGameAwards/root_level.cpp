// ì¬ŽÒ : ”Âê
#include "root_level.hpp"
#include "easy_engine.hpp"
#include "keyboard.hpp"
#include "test_level.hpp"
#include "test2d_level.hpp"

USING_NS_EGEG;

// ‰Šú‰»
bool RootLevel::initialize()
{
    EasyEngine::getInputDeviceManager()->connectDevice<Keyboard>();

    task_.setJob(this, &RootLevel::update );
    EasyEngine::getTaskManager()->registerJob(&task_);

    return true;
}

// I—¹ˆ—
void RootLevel::finalize()
{
    EasyEngine::getTaskManager()->unregisterJob(&task_);
}

// XVˆ—
void RootLevel::update( uint64_t )
{
    auto& key_status = EasyEngine::getInputDeviceManager()->getDevice<Keyboard>()->getState();

    if( InputDevice::isPressed(key_status.numpad_1) )
    {
        getManager()->transition<TestLevel>();
        return;
    }
    if( InputDevice::isPressed(key_status.numpad_2) )
    {
        getManager()->transition<Test2DLevel>();
        return;
    }
}

// EOF
