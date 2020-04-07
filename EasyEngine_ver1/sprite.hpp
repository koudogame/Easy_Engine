#pragma once
#include "actor.hpp"
#include "texture.hpp"
#include "rectangle_shape.hpp"
#include "uid.hpp"

class Sprite :
    public EGEG Actor
{
public :
    Sprite() : Actor( EGEG TypeID<Sprite>::getID() ) {}

    bool initialize() override;
    void finalize() override;
    void update( uint64_t ) override;
    const EGEG Shape* getShape() override;

    void collision( Actor* );
private :
    EGEG ITexture* p_textrue_;
    EGEG RectangleShape shape_;
};
