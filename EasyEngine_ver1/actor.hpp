///
/// @file   actor.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR_HEADER_
#define INCLUDED_EGEG_ACTOR_HEADER_
#include <cstdint>
#include <typeinfo>
#include <unordered_map>
#include "system_manager.hpp"
BEGIN_EGEG
class Shape;
class Component;
///
/// @class  Actor
///
/// @brief  アクター基底クラス
class Actor
{
public :
    virtual ~Actor();

    ///
    /// @brief  初期化処理
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間の差(: ミリ秒)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;

    ///
    /// @brief  形の取得
    ///
    /// @return 形
    ///
    virtual const Shape* getShape() = 0;

    ///
    /// @brief  アクター識別ID取得
    ///
    /// @return ID
    ///
    uint32_t getID() const { return id_; }

    ///
    /// @brief  コンポーネントの追加
    ///
    /// @tparam ComponentType : 追加するコンポーネント型
    ///
    /// @return 追加したコンポーネント
    ///
    template <typename ComponentType>
    ComponentType* addComponent();
    ///
    /// @brief  コンポーネントの削除
    ///
    /// @tparam ComponentType : 削除するコンポーネント型
    ///
    template <typename ComponentType>
    void removeComponent();
    ///
    /// @brief   コンポーネントの取得
    /// @details 対応したコンポーネントを保持していない場合は、nullptrを返却します。
    ///
    /// @tparam ComponentType : 取得するコンポーネント型
    ///
    /// @return コンポーネント
    ///
    template <typename ComponentType>
    ComponentType* getComponent();

protected :
    ///
    /// @brief   コンストラクタ
    /// @details 通常ファクトリ以外での生成を禁止しています。
    ///
    /// @param[in] ID : アクター識別ID
    ///
    Actor( uint32_t ID ) : id_( ID ) {}

private :
    uint32_t id_;                                           /// アクター識別ID
    std::unordered_map<uint32_t, Component*> components_;   /// コンポーネント群
};

///< コンポーネントの追加
template <typename ComponentType>
ComponentType* Actor::addComponent()
{
    // 多重登録チェック
    if( components_.find(ComponentType::getID()) != components_.end() )
    {
        SystemManager::instance()->showDialogBox(
            "コンポーネントの多重登録を検知しました。\n"
            "\n場所 : Actor::addComponent\n"
            "型 : " + typeid( ComponentType ).name()
        );
        return nullptr;
    }

    // コンポーネントの生成＆初期化
    ComponentType* component = new ComponentType( this );
    if( component->initialize() == false )
    {
        delete component;
        SystemManager::instance()->showDialogBox(
            "コンポーネントの初期化に失敗しました。\n"
            "\n場所 : Actor::addComponent\n"
            "型 : " + typeid( ComponentType ).name()
        );
        return nullptr;
    }

    // コンポーネントをリストに追加
    components_.emplace( ComponentType::getID(), component );
    return component;
}

///< コンポーネントの削除
template <typename ComponentType>
void Actor::removeComponent()
{
    if( auto find = components_.find(ComponentType::getID()) != components_.end() )
    {
        find->second->finalize();
        delete find->second;
        components_.erase( find );
    }
}

///< コンポーネントの取得
template <typename ComponentType>
ComponentType* Actor::getComponent()
{
    if( auto find = components_.find(ComponentType::getID()) != components_.end() )
    {
        return dynamic_cast<ComponentType*>( find->second );
    }
    else
        return nullptr;
}
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_HEADER_
/// EOF
