///
/// @file   sprite.hpp
/// @author 板場
///
#ifndef INCLUDED_SPRITE_HEADER_
#define INCLUDED_SPRITE_HEADER_

#include <memory>
#include "actor2d.hpp"
#include "type_id.hpp"
#include "task.hpp"
#include "sprite_vertex_shader.hpp"
#include "sprite_pixel_shader.hpp"
#include "rendering2d.hpp"

///
/// @class  Sprite
/// @brief  スプライト( 2D画像 )
///
class Sprite :
    public EGEG Actor2D
{
public :
    Sprite() :
        Actor2D( EGEG TypeID<Sprite>() )
    {
    }

    // overrides
    bool initialize() override;
    void finalize() override;
private :
    EGEG Task task_;
    std::unique_ptr<SpriteVertexShader> vertex_shader_;
    std::unique_ptr<SpritePixelShader>  pixel_shader_;
};

#endif /// !INCLUDED_SPRITE_HEADER_
/// EOF
