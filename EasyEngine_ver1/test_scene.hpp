#pragma once
#include "scene.hpp"
#include "sprite.hpp"

class TestScene :
    public EGEG Scene
{
public :
    static Scene* create() { return new TestScene(); }

/*-----------------------------------------------------------------*/
// Scene
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;
    void update( uint64_t ) override;

protected :
    TestScene() = default;

private :
    Sprite sprite_;
};
