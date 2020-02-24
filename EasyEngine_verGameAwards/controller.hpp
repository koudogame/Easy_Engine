///
/// @file   controller.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CONTROLLER_HEADER_
#define INCLUDED_EGEG_CONTROLLER_HEADER_
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Controller
/// @brief   コントローラー基底クラス
/// @details 各種デバイスに対応した派生クラスで、キーに対応した処理を登録します。
///
class Controller
{
public :
    virtual ~Controller() = default;

    ///
    /// @brief   入力状態の更新
    /// @details 保持している入力デバイスから入力を取得し、入力に対応した処理を実行します。
    ///
    virtual void update() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_CONTROLLER_HEADER_
/// EOF
