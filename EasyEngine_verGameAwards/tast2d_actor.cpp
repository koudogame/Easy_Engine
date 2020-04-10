#include "test2d_actor.hpp"
#include "easy_engine.hpp"
#include "transform2d.hpp"
#include "rendering2d.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
#include "test2d_vs.hpp"
#include "test2d_ps.hpp"
#include "input_device_manager.hpp"

USING_NS_EGEG;

bool Test2DActor::initialize()
{
    task_.setJob( this, &Test2DActor::update );
    EasyEngine::getTaskManager()->registerJob( &task_ );

    auto render = addComponent<component::Rendering2D>();
    render->setTexture( EasyEngine::getRenderingManager()->getTextureLoader()->load(L"pyoro.png") );
    if( !render->getTexture() )
        return false;
    render->setTrimmingRange( { 0L, 0L, 64L, 64L } );

    vs_ = EasyEngine::getRenderingManager()->getShaderLoader()->loadVertexShader<Test2DVertexShader>();
    if( !vs_ ) return false;
    render->setVertexShader( vs_.get() );
    ps_ = EasyEngine::getRenderingManager()->getShaderLoader()->loadPixelShader<Test2DPixelShader>();
    if( !ps_ ) return false;
    render->setPixelShader( ps_.get() );

    auto transform = addComponent<component::Transform2D>();
    transform->setPivot( {0.0F, 0.0F} );
    transform->setRotation( 0.0F );
    transform->setPosition( {0.0F, 0.0F} );
    transform->setScale( {1.0F, 1.0F} );
    return true;
}

void Test2DActor::finalize()
{

}

void Test2DActor::update( uint64_t )
{
    auto& state = EasyEngine::getInputDeviceManager()->getDevice<Keyboard>()->getState();

    if( InputDevice::isInput( state.right ) )
    {
        auto transform = getComponent<component::Transform2D>();
        transform->setRotation( transform->getRotation() + 1.0F);
    }
}
