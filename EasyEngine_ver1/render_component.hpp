///
/// @file   render_component.hpp
/// @author 板場
///
/// @brief  描画コンポーネント
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#include "component.hpp"
#include "component_id.hpp"
BEGIN_EGEG
class RenderComponent :
    public IComponent
{
public :
    DECL_GETCOMPONENTID { return ComponentID::kRenderComponent; }

    virtual ~RenderComponent() = default;

    ///
    /// @brief  描画処理
    ///
    virtual void render() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
