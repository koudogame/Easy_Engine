///
/// @file   actor2d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR2D_HEADER_
#define INCLUDED_EGEG_ACTOR2D_HEADER_
#include <cassert>
#include <list>
#include <unordered_map>
#include "actor.hpp"
#include "uid.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class Component;

///
/// @class  Actor2D
/// @brief  2Dアクター
///
class Actor2D :
    public Actor
{
public :
    ///< デストラクタ
    virtual ~Actor2D() noexcept
    {
        if( parent_ ) parent_->removeChild( this );
    }

    ///
    /// @brief  座標の設定
    ///
    /// @param[in] Destination : 座標
    ///
    void setPosition( const Vector2D& Destination ) noexcept { position_ = Destination; }
    ///
    /// @brief  座標の取得
    ///
    /// @return 座標
    ///
    const Vector2D& getPosition() const noexcept { return position_; }

    ///
    /// @brief  親アクターの設定
    ///
    /// @param[in] Parent : 設定する親アクター
    ///
    void setParent( Actor2D* Parent ) noexcept { parent_ = Parent; }
    ///
    /// @brief  子アクターの追加
    ///
    /// @param[in] Child : 追加する子アクター
    ///
    void addChild( Actor2D* Child ) noexcept { assert(Child); Child->setParent( this ); childs_.push_back( Child ); }
    ///
    /// @brief  子アクターの削除
    ///
    /// @param[in] Child : 削除対象の子アクター
    ///
    void removeChild( Actor2D* Child ) noexcept { childs_.remove( Child ); }

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
    Actor2D* parent_ = nullptr;
    std::list<Actor2D*> childs_;

private :
    Vector2D position_{ 0.0F, 0.0F };
    std::unordered_map<uint32_t, Component*> components_;
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
    components_.emplace( UID<ComponentType>(), component );

    return component;
}

///< コンポーネントの取得
template <class ComponentType>
ComponentType* Actor2D::getComponent() const
{
    auto find = components_.find( UID<ComponentType>() );
    if( find == components_.end() ) return nullptr;

    // 対応するコンポーネントを返却
    return static_cast<ComponentType*>( find->second );
}
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR2D_HEADER_
/// EOF
