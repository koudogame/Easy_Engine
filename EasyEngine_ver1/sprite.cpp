#include "sprite.hpp"
#include "texture_manager.hpp"
#include "sprite_component.hpp"
#include "collision_component.hpp"

using namespace easy_engine;

bool Sprite::initialize()
{
    TextureManager::instance()->load( L"kirby.png", &p_textrue_ );
    SpriteComponent* sprite = addComponent<SpriteComponent>();
    sprite->setStatus(
        p_textrue_,
        { 0.0F, 0.0F },
        { 0.0, 0.0F, 64.0F, 64.0F }
    );
    
    shape_.setPosition( { 0.0F, 0.0F } );
    shape_.setHeight( 64.0F );
    shape_.setHeight( 64.0F );
    CollisionComponent* collision = addComponent<CollisionComponent>();
    collision->setPostCollision( getID(), this, &Sprite::collision );

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
    return &shape_;
}

void Sprite::collision( Actor* pOther )
{
    //_asm int 3;
}
