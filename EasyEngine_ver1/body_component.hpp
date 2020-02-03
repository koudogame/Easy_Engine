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
///
/// @class   BodyComponent
/// @brief   衝突判定用コンポーネント
///
/// @details 衝突用コンポーネント<br>
///          衝突判定は、ダブルディスパッチを使用して行います。
///
class BodyComponent :
    public Component
{
public :
    ///< IDの取得
    static uint32_t getID() { return UID<BodyComponent>::getID(); }

    virtual ~BodyComponent() = default;

    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] Owner : オーナー
    ///
    BodyComponent( Actor* Owner ) : Component( Owner ) {}

    ///
    /// @brief  アクターとの衝突判定
    ///
    /// @param[in] Other : 判定を行うアクター
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( Actor* Other );

    ///
    /// @brief   衝突後処理の追加
    /// @details IDに対応した処理が既にある場合は上書き
    ///
    /// @tparam ActorType : オーナーの型(省略可)
    ///
    /// @param[in] OtherID   : 処理に対応するアクターのID
    /// @param[in] pCallBack : 衝突時に呼び出される関数のアドレス
    ///
    template <typename ActorType>
    void postCollision( uint32_t OtherID, void(ActorType::*pCallBack)(Actor*) );

protected :
    std::unordered_map<uint32_t, std::function<void(Actor*)> > post_collision_;
};

///< 衝突後処理の追加
template <typename ActorType>
void BodyComponent::postCollision( uint32_t OtherID, void(ActorType::*pCallBack)(Actor*) )
{
    post_collision_.erase( OtherID );
    post_collision_.emplace( 
        OtherID,
        std::bind<void(Actor*)>(pCallBack, owner_, std::placeholders::_1)
    );
}
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_COMPONENT_HEADER_
/// EOF
