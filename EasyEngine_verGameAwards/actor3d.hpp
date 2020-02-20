///
/// @file   actor3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR3D_HEADER_
#define INCLUDED_EGEG_ACTOR3D_HEADER_
#include <cassert>
#include <unordered_map>
#include "actor.hpp"
#include "uid.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class Component;

///
/// @class  Actor3D
/// @brief  3Dアクター
///
class Actor3D :
    public Actor
{
public :
    ///
    /// @brief  座標の設定
    ///
    /// @param[in] Destination : 座標
    ///
    void setPosition( const Vector3D& Destination ) noexcept { position_ = Destination; }
    ///
    /// @brief  座標の取得
    ///
    /// @return 座標
    ///
    const Vector3D& getPosition() const noexcept { return position_; }

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
    /// @details 対応するコンポーネントがない場合、nullptrを返却します。
    ///
    /// @tparam ComponentType : 取得するコンポーネント型
    ///
    /// @return コンポーネント
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

protected :
    Actor3D( uint32_t ActorID ) noexcept : Actor( ActorID ) {}

private :
    Vector3D position_;
    std::unordered_map<uint32_t, Component*> components_;
};

///< コンポーネントの追加
template <class ComponentType>
ComponentType* Actor3D::addComponent()
{
    assert( getComponent<ComponentType>() == nullptr &&
        "コンポーネントの多重登録を検出しました。" );

    // コンポーネントの生成
    ComponentType component = new ComponentType( this );
    component->initialize();

    // 生成したコンポーネントをリストに追加
    components_.emplace( UID<ComponentType>(), component );

    return component;
}

///< コンポーネントの取得
template <class ComponentType>
ComponentType* Actor3D::getComponent() const
{
    auto find = components_.find( UID<ComponentType>() );
    if( find == components_.end() ) return nullptr;

    // 対応するコンポーネントの返却
    return static_cast<ComponentType*>( find->second );
}
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR3D_HEADER_
/// EOF
