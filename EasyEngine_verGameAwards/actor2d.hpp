///
/// @file   actor2d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR2D_HEADER_
#define INCLUDED_EGEG_ACTOR2D_HEADER_

#include <cassert>
#include <list>
#include "actor.hpp"
#include "type_id.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Actor2D
/// @brief  2Dアクター
///
class Actor2D :
    public Actor
{
public :
    ///< デストラクタ
    virtual ~Actor2D() = default;

    ///
    /// @brief  コンポーネントの追加
    ///
    /// @tparam ComponentType : 追加するコンポーネント型
    ///
    /// @return 追加したコンポーネント
    ///
    template <class ComponentType>
    ComponentType* addComponent();
    ///
    /// @brief   コンポーネントの取得
    /// @details 対応したコンポーネントを所持していない場合、nullptrを返却します。
    ///
    /// @tparam ComponentType : 取得するコンポーネント型
    ///
    /// @return コンポーネント
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

protected :
    Actor2D( uint32_t ActorID ) noexcept : Actor( ActorID ) {}
};


///< コンポーネントの追加
template <class ComponentType>
ComponentType* Actor2D::addComponent()
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

///< コンポーネントの取得
template <class ComponentType>
ComponentType* Actor2D::getComponent() const
{
    auto find = components_.find( ComponentType::getID() );
    if( find == components_.end() ) return nullptr;

    // 対応するコンポーネントを返却
    return static_cast<ComponentType*>( find->second );
}

END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR2D_HEADER_
/// EOF
