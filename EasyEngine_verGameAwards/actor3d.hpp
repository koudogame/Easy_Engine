///
/// @file   actor3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR3D_HEADER_
#define INCLUDED_EGEG_ACTOR3D_HEADER_

#include <cassert>
#include "actor.hpp"
#include "type_id.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Actor3D
/// @brief  3Dアクター
///
class Actor3D :
    public Actor
{
public :
    ///
    /// @brief  コンポーネントの追加
    ///
    /// @tparam ComponentType : 追加するコンポーネント型
    ///
    /// @return 追加したコンポーネント
    ///
    template <class ComponentType>
    ComponentType* addComponent();

protected :
    Actor3D( uint32_t ActorID ) noexcept : Actor( ActorID ) {}
};

///< コンポーネントの追加
template <class ComponentType>
ComponentType* Actor3D::addComponent()
{
    assert( getComponent<ComponentType>() == nullptr &&
        "コンポーネントの多重登録を検出しました。" );

    // コンポーネントの生成
    ComponentType* component = new ComponentType( this );
    component->initialize();

    // 生成したコンポーネントをリストに追加
    components_.emplace( ComponentType::getID(), component );

    return component;
}

END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR3D_HEADER_
/// EOF
