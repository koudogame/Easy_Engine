///
/// @file   body_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_BODY_COMPONENT_HEADER_
#define INCLUDED_EGEG_BODY_COMPONENT_HEADER_
#include <functional>
#include <unordered_map>
#include "component.hpp"
#include "uid.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"

BEGIN_EGEG
class CollisionSection;

///
/// @class   CollisionComponent
/// @brief   衝突判定用コンポーネント
///
/// @details 衝突用コンポーネント<br>
///          衝突判定は、ダブルディスパッチを使用して行います。
///
class CollisionComponent :
    public Component
{
public :
    ///< IDの取得
    static uint32_t getID() { return UID<CollisionComponent>::getID(); }

    virtual ~CollisionComponent() = default;

    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pOwner : オーナー
    ///
    CollisionComponent( Actor* pOwner ) : Component( pOwner ) {}

    ///
    /// @brief  衝突を通知
    ///
    /// @param[in] pOther : 衝突を検出したコンポーネント
    ///
    virtual void notifyCollision( const CollisionComponent* pOther );

    ///
    /// @brief   衝突後処理の設定
    /// @details IDに対応した処理が既にある場合は上書きします。
    ///
    /// @tparam ActorType : オーナーの型(省略可)
    ///
    /// @param[in] OtherID   : 処理に対応するアクターのID
    /// @param[in] pOwner    : 関数の実行者
    /// @param[in] pCallBack : 衝突時に呼び出される関数のアドレス
    ///
    template <typename ActorType>
    void setPostCollision( uint32_t OtherID, ActorType* pOwner, void(ActorType::*pCallBack)(Actor*) );

    ///
    /// @brief  形の取得
    ///
    /// @return オーナーの形
    ///
    const Shape* getShape() const { return owner_->getShape(); }

    ///
    /// @brief  所属セクションの設定
    ///
    /// @param[in] pSection : セクション
    ///
    void setBelongSection( CollisionSection* pSection ) { section_ = pSection; }
    ///
    /// @brief  所属セクションの取得
    ///
    /// @return 所属セクション
    ///
    CollisionSection* getBelongSection() const { return section_; }

/*-----------------------------------------------------------------*/
// Component
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

protected :
    std::unordered_map<uint32_t, std::function<void(Actor*)> > post_collision_;

private :
    CollisionSection* section_ = nullptr;   /// 自身の所属する空間セクション
};

///< 衝突後処理の追加
template <typename ActorType>
void CollisionComponent::setPostCollision( uint32_t OtherID, ActorType* pOwner, void(ActorType::*pCallBack)(Actor*) )
{
    post_collision_.erase( OtherID );
    post_collision_.emplace( 
        OtherID,
        std::bind(pCallBack, pOwner, std::placeholders::_1)
    );
}
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_COMPONENT_HEADER_
/// EOF
