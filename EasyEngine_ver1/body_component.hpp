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
    /// @brief   ファーストディスパッチ
    /// @details 実装は、アクターのBodyComponentのisCollision関数に、具体的な形を渡して呼び出します。<br>
    ///          衝突を検出した場合、衝突後の処理が呼び出されます。
    ///
    /// @param[in] Other : 衝突を判定するアクター
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( Actor* Other ) = 0;
    ///
    /// @brief  矩形との衝突判定
    ///
    /// @param[in] Rectangle : 衝突を判定する矩形
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Rectangle& Rectangle ) = 0;
    ///
    /// @brief  円形との衝突判定
    ///
    /// @param[in] Circle : 衝突を判定する円形
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Circle& Circle ) = 0;
    ///
    /// @brief  線分との衝突判定
    ///
    /// @param[in] Line : 衝突を判定する線分
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    virtual bool isCollided( const Line& Line ) = 0;

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
