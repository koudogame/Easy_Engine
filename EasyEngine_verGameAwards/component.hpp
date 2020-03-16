///
/// @file   component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include "egeg.hpp"
BEGIN_EGEG
class Actor;

///
/// @class   Component
/// @brief   コンポーネント基底
/// @details 派生クラスはコンポーネントIDを返却する関数を<br>
///          static uint32_t getID() として定義して下さい。
///
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @return 成功[ true ]　失敗[ false ]
    ///
    virtual bool initialize() = 0;

    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;

protected :
    Component( Actor* Owner ) : owner_( Owner ) {}
    Actor* owner_;  ///< 自身を保持しているアクター
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
