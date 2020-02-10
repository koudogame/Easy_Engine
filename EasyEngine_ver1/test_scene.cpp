#include "test_scene.hpp"
#include "scene_factory.hpp"
#include "uid.hpp"

REGISTER_SCENE( 0U, &TestScene::create );

bool TestScene::initialize()
{
    sprite_.initialize();
    sprite_1.initialize();

    return true;
}

void TestScene::finalize()
{
    sprite_.finalize();
    sprite_1.finalize();
}

void TestScene::update( uint64_t )
{
}
