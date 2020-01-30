// 作成者 : 板場
#include "actor.hpp"
#include "system_manager.hpp"
#include "component_factory.hpp"

BEGIN_EGEG
// Actor : 関数の実装
/*===========================================================================*/
// デストラクタ
Actor::~Actor()
{
    // 保持しているコンポーネントの解放
    for( auto& component : components_ )
    {
        component.second->finalize();
        delete component.second;
    }
}

// コンポーネントの追加
Component* Actor::addComponent( uint32_t ComponentID )
{
    auto find = components_.find( ComponentID );
    if( find != components_.end() )
    {
        SystemManager::instance()->showDialogBox(
            "コンポーネントの多重登録を検知しました。\n"
            "\n場所 : Actor::addComponent"
        );
        return nullptr;
    }

    // コンポーネントの生成＆初期化
    Component* component = ComponentFactory::instance()->create( ComponentID, this );
    if( component == nullptr )
    {
        SystemManager::instance()->showDialogBox(
            "コンポーネントの生成に失敗しました。\n"
            "\n場所 : Actor::addComponent"
        );
        return nullptr;
    }
    if( component->initialize() == false )
    {
        SystemManager::instance()->showDialogBox(
            "コンポーネントの初期化に失敗しました。\n"
            "\n場所 : Actor::addComponent"
        );
        delete component;
        return nullptr;
    }

    // コンポーネントをリストに追加
    components_.emplace( ComponentID, component );
    return component;
}

// コンポーネントの削除
void Actor::removeComponent( uint32_t ComponentID )
{
    auto find = components_.find( ComponentID );
    if( find != components_.end() )
    {
        find->second->finalize();
        delete find->second;
        components_.erase( find );
    }
}

// コンポーネントの取得
Component* Actor::getComponent( uint32_t ComponentID )
{
    auto find = components_.find( ComponentID );
    if( find != components_.end() )
        return find->second;
    else
        return nullptr;
    
}
END_EGEG
// EOF
