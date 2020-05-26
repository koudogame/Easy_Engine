///
/// @file   component2d.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_COMPONENT2D_HEADER_
#define INCLUDED_EGEG_COMPONENT2D_HEADER_

#include "component.hpp"
#include "actor2d.hpp"

BEGIN_EGEG

///
/// @class Component2D
/// @brief 2Dアクター用コンポーネント
///
class Component2D :
    public Component
{
public :
    Component2D( Actor2D* Owner ) :
        Component{ Owner }
    {}

    ///
    /// @brief オーナーの取得( overload )
    ///
    /// @return オーナー
    ///
    /// @details オーナーはActor2Dから派生していることが確定しているので <br>
    ///           戻り値の型はActor2D*
    ///
    Actor2D* getOwner() const noexcept { return static_cast<Actor2D*>(getOwner()); }
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT2D_HEADER_
/// EOF
