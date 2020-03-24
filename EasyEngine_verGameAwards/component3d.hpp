///
/// @file   component3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COMPONENT3D_HEADER_
#define INCLUDED_EGEG_COMPONENT3D_HEADER_
#include "component.hpp"
#include "actor3d.hpp"

BEGIN_EGEG
namespace component {

///
/// @class  Component3D
/// @brief  3Dアクター用コンポーネント
///
class Component3D :
    public Component
{
public :
    Component3D( Actor3D* Owner ) :
        Component( Owner )
    {}

    Actor3D* getOwner() const noexcept { return static_cast<Actor3D*>(owner_); }
};

} /// namespace component
END_EGEG
#endif /// INCLUDED_EGEG_COMPONENT3D_HEADER_
/// EOF
