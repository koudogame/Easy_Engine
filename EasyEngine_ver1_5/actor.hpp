///
/// @file   actor.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_ACTOR_HEADER_
#define INCLUDED_EGEG_ACTOR_HEADER_

#include <cstdint>
#include <unordered_map>
#include <memory>
#include <DirectXMath.h>
#include "factory.hpp"
#include "name.hpp"
#include "id.hpp"

BEGIN_EGEG

class Level;     ///< レベル前方宣言( 循環参照回避 )
class Component; ///< コンポーネント前方宣言( 循環参照回避 )


///
/// @def    REGISTER_ACTOR
/// @brief  アクターをファクトリに登録
///
/// @param[in] ActorType : 登録するアクター型
/// @param[in] ActorName : アクターの名前( .lvlファイルで使用します。)
///
#define REGISTER_ACTOR( ActorType, ActorName ) \
static constexpr const char ActorType ## Name[] = #ActorName; \
REGISTER_WITH_FACTORY( ActorFactory, ActorType, Name<ActorType ## Name> )


///
/// @class Actor
/// @brief オブジェクト単位
///
class Actor
{
public :
    ///
    /// @brief コンストラクタ
    ///
    /// @param[in] ID : アクターID
    ///
    Actor( uint32_t ID ) noexcept :
        id_{ ID },
        affiliation_level_{ nullptr }
    {}
    virtual ~Actor() = default;

    ///
    /// @brief 初期化
    ///
    /// @param[in] DataStream : データを抽出するストリーム
    ///
    /// @return true:成功　false:失敗
    ///
    virtual bool initialize( std::istream& DataStream ) = 0;

    ///
    /// @brief 終了
    ///
    virtual void finalize() = 0;


    ///
    /// @brief アクターIDの取得
    ///
    /// @return アクターID
    ///
    uint32_t getID() const noexcept { return id_; }

    ///
    /// @brief 所属先レベルの取得
    ///
    /// @return 所属先レベル
    ///
    Level* getAffiliationLevel() const noexcept { return affiliation_level_; }

    ///
    /// @brief コンポーネントの取得
    ///
    /// @tparam ComponentType : 取得するコンポーネントの型
    ///
    /// @return コンポーネント
    ///
    /// @details 対応するコンポーネントを保持していない場合、nullptrを返却します。
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

    ///
    /// @brief コンポーネントの削除
    ///
    /// @tparam ComponentType : 削除するコンポーネントの型
    ///
    /// @details 対応するコンポーネントを保持していない場合、何も行いません。
    ///
    template <class ComponentType>
    void removeComponent() noexcept;


    ///
    /// @brief ワールド変換行列を計算
    ///
    /// @return ワールド変換行列
    ///
    /// @details Actor2D, Actor3Dによって実装されます。
    ///
    virtual DirectX::XMMATRIX calcWorldMatrix() const = 0;

    ///
    /// @brief 所属するレベルのセット
    ///
    /// @param[in] Affiliation : 所属先レベル
    ///
    /// @details レベルにより呼び出される関数です。
    ///
    void setAffiliationLevel( Level& Affiliation ) noexcept { affiliation_level_ = &Affiliation;}
protected :
    ///< コンポーネントのデリーター
    struct ComponentDeleter
    {
        void operator()( Component* ) const;
    };
    std::unordered_map<uint32_t, std::unique_ptr<Component, ComponentDeleter>> components_;
private :
    uint32_t id_;
    Level* affiliation_level_;
};


///< アクターファクトリの前方宣言
template class Factory<std::string, Actor>;
using ActorFactory = Factory<std::string, Actor>;


///< コンポーネントの取得関数定義
template <class ComponentType>
ComponentType* Actor::getComponent() const
{
    auto find_itr = components_.find( TypeID<ComponentType>{} );
    if( find_itr == components_.end() ) return nullptr;

    return static_cast<ComponentType*>( find_itr->second.get() );
}

///< コンポーネントの削除関数定義
template <class ComponentType>
void Actor::removeComponent() noexcept
{
    components_.erase( TypeID<ComponentType>{} );
}


END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_HEADER_
/// EOF
