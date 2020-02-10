#pragma once
#include "actor.hpp"
#include "texture.hpp"


class Sprite :
    public EGEG Actor
{
public :
    Sprite() : Actor( 0 ) {}

    bool initialize() override;
    void finalize() override;
    void update( uint64_t ) override;
    const EGEG Shape* getShape() override;
private :
    EGEG ITexture* p_textrue_;
};
