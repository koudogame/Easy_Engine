///
/// @file   component2d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COMPONENT2D_HEADER_
#define INCLUDED_EGEG_COMPONENT2D_HEADER_

#include "component.hpp"
#include "actor2d.hpp"

BEGIN_EGEG
namespace component
{

///
/// @class  Component2D
/// @brief  2Dアクター用コンポーネント
///
class Component2D :
    public Component
{
public :
    Component2D( Actor2D* Owner ) :
        Component( Owner )
    {}

    Actor2D* getOwner() const noexcept { return static_cast<Actor2D*>(owner_); }
};

} // namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT2D_HEADER_
/// EOF
