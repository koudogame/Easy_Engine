///
/// @file   controller.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CONTROLLER_HEADER_
#define INCLUDED_EGEG_CONTROLLER_HEADER_
#include "noncopyable.hpp"
#include "input_device.hpp"
BEGIN_EGEG
///
/// @class   Controller
/// @brief   コントローラー基底クラス
/// @details 各種デバイスに対応した派生クラスで、キーに対応した処理を登録します。<br>
///          意図せずに複数のコントローラ－から一つのオブジェクトが操作されることを防ぐために、コピーを禁止しています。
///
class Controller : 
    NonCopyable<Controller>
{
public :
    /// 特殊メンバ関数 - ムーブは許可
    Controller()                          = default;
    virtual ~Controller()                 = default;
    Controller( Controller&& )            = default;
    Controller& operator=( Controller&& ) = default;

    ///
    /// @brief   入力状態の更新
    /// @details 保持している入力デバイスから入力を取得し、入力に対応した処理を実行します。
    ///
    virtual void update() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_CONTROLLER_HEADER_
/// EOF
