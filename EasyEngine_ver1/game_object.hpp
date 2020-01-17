///
/// @file   game_object.hpp
/// @author 板場
///
/// @brief  ゲーム中に存在するオブジェクトの基底クラス
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif /// !_DEBUG
#include <unordered_map>
#include "component.hpp"
BEGIN_EGEG
class GameObject
{
public :
    virtual ~GameObject() = default;

    ///
    /// @brief  初期化処理
    /// 
    /// @return 初期化成功[ true ] 初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;
    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTime : 前回呼び出しからの経過時間(: ミリ秒)
    ///
    virtual void update( uint64_t DeltaTime ) = 0;

    ///
    /// @brief   コンポーネントの追加
    /// @details 追加に失敗した場合、nullptrを返却します。
    ///
    /// @tparam Component : 追加するコンポーネントの型
    ///
    /// @return 追加したコンポーネントのアドレス
    ///
    template <typename Component>
    Component* addComponent();
    ///
    /// @brief   コンポーネントの取得
    /// @details 対応するコンポーネントが無かった場合、nullptrを返却します。
    ///
    /// @tparam Component : 取得するコンポーネントの型
    ///
    /// @return 取得されたコンポーネントのアドレス
    ///
    template <typename Component>
    Component* getComponent();

protected :
    std::unordered_map<uint16_t, IComponent*> components_;  ///< 登録されているコンポーネント群
};


///< GameObject : コンポーネントの追加
template <typename Component>
Component* GameObject::addComponent()
{
#ifdef _DEBUG
    assert( components_.find(Component::getComponentID()) == components_.end() &&
            "コンポーネントの多重登録を検出しました。" );
#endif /// !_DEBUG
    Component* add = new Component();
    if( add->initialize() == false )
    {
        delete add;
        return nullptr;
    }

    components_.emplace( Component::getComponentID(), add );
}

///< GameObject : コンポーネントの取得
template <typename Component>
Component* GameObject::getComponent()
{
    auto find = components_.find( Component::getComponentID() );
    
    ///< コンポーネントが登録されている
    if( find != components_.end() )
    {
        return find->second;
    }
    ///< コンポーネントが登録されていない
    else
    {
        return nullptr;
    }
}
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_HEADER_
/// EOF
