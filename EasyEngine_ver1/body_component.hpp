///
/// @file   body_component.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_BODY_COMPONENT_HEADER_
#define INCLUDED_EGEG_BODY_COMPONENT_HEADER_
#include <functional>
#include <unordered_map>
#include "component.hpp"
BEGIN_EGEG
///
/// @class   BodyComponent
/// @details ëÃ
///
class BodyComponent :
    public Component
{
public :
    BodyComponent( Actor* Owner ) : Component( Owner ) {}



private :
    std::unordered_map<uint32_t, std::function<void(Actor*)> > f_post_collision_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_COMPONENT_HEADER_
/// EOF
