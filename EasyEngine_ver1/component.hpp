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
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] Owner : オーナー
    ///
    Component( Actor* Owner ) : owner_( Owner ) {}
    virtual ~Component() = default;

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

protected :
    Actor* owner_;    ///< オーナー
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
