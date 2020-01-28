///
/// @file   scene.hpp
/// @author î¬èÍ
///
/// @brief  ÉVÅ[Éì
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include <cstdint>
#include "game_object.hpp"
BEGIN_EGEG
class Scene :
    public GameObject
{
public :
    virtual ~Scene() = default;

    void setActive( bool State ) { is_active_ = State; }
    bool isActive() const { return is_active_; }

private :
    bool is_active_ = false;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
