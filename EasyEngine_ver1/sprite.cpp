#include "sprite.hpp"
#include "texture_manager.hpp"
#include "sprite_component.hpp"

using namespace easy_engine;

bool Sprite::initialize()
{
    TextureManager::instance()->load( L"kirby.png", &p_textrue_ );
    SpriteComponent* component = addComponent<SpriteComponent>();

    component->setStatus(
        p_textrue_,
        { 0.0F, 0.0F },
        { 0.0, 0.0F, 64.0F, 64.0F }
    );

    return true;
}

void Sprite::finalize()
{
    TextureManager::instance()->unload( &p_textrue_ );
}

void Sprite::update( uint64_t )
{

}

const Shape* Sprite::getShape()
{
    return nullptr;
}
