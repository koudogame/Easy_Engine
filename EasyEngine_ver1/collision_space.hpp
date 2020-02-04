///
/// @file   collision_space.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#define INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class   ICollisionSpace
/// @brief   衝突空間インターフェイス
///          
/// @details 衝突判定を行う空間のインターフェイスです。
///
class ICollisionSpace
{
public :
    virtual ~ICollisionSpace() = default;

    ///
    /// @brief  空間への登録
    ///
    /// @param[in] pComponent : 登録するコンポーネントのアドレス
    ///
    virtual void entry( CollisionComponent* pComponent ) = 0;
    ///
    /// @brief  空間から削除
    ///
    /// @param[in] pComponent : 削除するコンポーネントのアドレス
    ///
    virtual void exit( CollisionComponent* pComponent ) = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_SPACE_HEADER_
/// EOF
