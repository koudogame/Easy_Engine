///
/// @file   controller.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_CONTROLLER_HEADER_
#define INCLUDED_EGEG_CONTROLLER_HEADER_

#include "non_copyable.hpp"

BEGIN_EGEG

///
/// @class   Controller
/// @brief   コントローラー
/// @details 各種デバイスに対応した派生クラスで、入力に対応した処理を登録します。 <br>
///           意図せず複数のコントローラーから１つのオブジェクトが操作されることを防ぐため、コピーを禁止しています。
///
class Controller :
    NonCopyable<Controller>
{
public :
    Controller() = default;
    virtual ~Controller() = default;
    Controller( const Controller& ) = delete;
    Controller& operator=( const Controller& ) = delete;
    Controller( Controller&& ) = default;
    Controller& operator=( Controller&& ) = default;

    ///
    /// @brief   更新
    /// @details 入力デバイスからの入力に対応した処理を実行します。
    ///
    virtual void update() = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CONTROLLER_HEADER_
/// EOF
