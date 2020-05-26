///
/// @file   component3d.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_COMPONENT3D_HEADER_
#define INCLUDED_EGEG_COMPONENT3D_HEADER_

#include "component.hpp"
#include "actor3d.hpp"

BEGIN_EGEG

///
/// @class Component3D
/// @brief 3Dアクター用コンポーネント
///
class Component3D :
    public Component
{
public :
    Component3D( Actor3D* Owner ) :
        Component{ Owner }
    {}

    ///
    /// @brief  オーナーの取得( overload )
    ///
    /// @return オーナー
    ///
    /// @details オーナーはActor3Dから派生していることが確定しているので <br>
    ///           戻り値の型はActor3D*
    ///
    Actor3D* getOwner() const noexcept { return static_cast<Actor3D*>(getOwner()); }
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT3D_HEADER_
/// EOF
