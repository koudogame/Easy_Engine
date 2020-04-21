///
/// @file   actor.hpp
/// @author 板場
///
#ifndef INCLUDED_ACTOR_HEADER_
#define INCLUDED_ACTOR_HEADER_
#include <cstdint>
#include <unordered_map>
#include "egeg.hpp"
BEGIN_EGEG
namespace component { class Component; } ///< コンポーネント前方宣言( 循環参照回避 )

///
/// @class  Actor
/// @brief  アクター基底
///
class Actor
{
public :
    virtual ~Actor();

    ///
    /// @brief  アクター識別IDの取得
    ///
    /// @return アクター識別ID
    ///
    uint32_t getID() const noexcept { return id_; }

    ///
    /// @brief  アクター初期化処理
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  アクター終了処理
    ///
    virtual void finalize() = 0;
    
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
    Actor( uint32_t ActorID ) noexcept : id_( ActorID ) {}
    std::unordered_map<uint32_t, component::Component*> components_; ///< コンポーネント

private :
    uint32_t id_;   /// アクター識別ID
};

///< コンポーネントの取得
template <class ComponentType>
ComponentType* Actor::getComponent() const
{
    auto find = components_.find( ComponentType::getID() );
    if( find == components_.end() ) return nullptr;

    // 対応するコンポーネントの返却
    return static_cast<ComponentType*>( find->second );
}

END_EGEG
#endif /// !INCLUDED_ACTOR_HEADER_
/// EOF
