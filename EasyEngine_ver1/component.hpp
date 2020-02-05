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
/// @detaisl Actorクラスのオーナーに対して影響します。<br>
///          派生クラスは static uint32_t getID()を実装してください。<br>
///          
///
class Component :
    public GameObject
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] Owner : オーナー
    ///
    Component( Actor* Owner ) : owner_( Owner ) {}
    virtual ~Component() = default;

protected :
    Actor* owner_;    ///< オーナー
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
