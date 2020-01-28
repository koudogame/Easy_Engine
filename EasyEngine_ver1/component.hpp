///
/// @file   component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include "actor.hpp"
BEGIN_EGEG
///
/// @class   Component
///          
/// @brief   コンポーネント基底クラス
/// @detaisl Actorクラスのオーナーに対して影響します。
///
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @param[in] pOwner : オーナーのアドレス
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize( Actor* pOwner ) = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;

protected :
    Actor* owner_ = nullptr;    ///< オーナー
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
