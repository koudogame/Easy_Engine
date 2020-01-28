///
/// @file   component.hpp
/// @author 板場
///
/// @brief  コンポーネント
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include "egeg_common.hpp"
BEGIN_EGEG
class GameObject;
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @param[in] Owner : オーナーのアドレス
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize( GameObject* Owner ) = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;

protected :
    GameObject* owner_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
