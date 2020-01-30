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
///
/// @def    DEF_FIRST_DISPATCH
/// @brief  ファーストディスパッチを定義します。
///
#define DEG_FIRST_DISPATCH  bool isCollision( Actor* Other ) override { if( auto com = Other->getComponent<BodyComponent>() ) { return com->isCollision( this ); } return false; }

BEGIN_EGEG 
///
/// @class   BodyComponent
/// @details 衝突用コンポーネント<br>
///          衝突判定は、ダブルディスパッチを使用して行います。<br>
///          ファーストディスパッチ関数はマクロを使用して定義して下さい。<br>
///          必要に応じて、具体的な型との衝突処理を追加して下さい。<br>
///          衝突判定関数のシグネチャは bool isCollision( Type* )です。
///
class BodyComponent :
    public Component
{
public :
    ///< IDの取得
    static uint32_t getID() { return UID<BodyComponent>::getID(); }

    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] Owner : オーナー
    ///
    BodyComponent( Actor* Owner ) : Component( Owner ) {}


    ///
    /// @brief   衝突後処理の追加
    /// @details 既にある場合は上書き
    ///
    /// @tparam ActorType : オーナーの型(省略可)
    ///
    /// @param[in] OtherID   : 処理に対応するアクターのID
    /// @param[in] pCallBack : 衝突時に呼び出される処理
    ///
    template <typename ActorType>
    void postCollision( uint32_t OtherID, void(ActorType::*pCallBack)(Actor*) );

    ///
    /// @brief  ファーストディスパッチ
    ///
    /// @param[in] Other : 衝突を判定するアクター
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollision( Actor* Other ) = 0;

    ///
    /// @brief  不明な形との衝突判定
    ///
    /// @return 常に[ false ]
    ///
    bool isCollision( BodyComponent* ) { return false; }
private :
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
