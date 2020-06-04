///
/// @file   component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_

#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  Component
/// @brief  コンポーネント
///
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  初期化
    ///
    /// @return true:成功　false:失敗
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  オーナーの取得
    ///
    /// @return オーナー
    ///
    LevelNode* getOwner() const noexcept { return owner_; }

private :
    LevelNode* owner_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
