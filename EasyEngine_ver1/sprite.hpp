///
/// @file   sprite.hpp
/// @author 板場
///
/// @brief  スプライト
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_
#include "render_component.hpp"
#include "egeg_math.hpp"
#include "texture.hpp"
BEGIN_EGEG
class SpriteComponent :
    public RenderComponent
{
public :

// RenderComponent
/*-----------------------------------------------------------------*/
    void render() override;

// IComponent
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
