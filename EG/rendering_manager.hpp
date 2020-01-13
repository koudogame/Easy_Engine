///
/// @file    rendering_manager.hpp
/// @author  板場
///          
/// @brief   レンダリングマネージャ―
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
#ifndef INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
#include "renderer.hpp"
BEGIN_EGEG
class RenderingManager
{
public :
    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static RenderingManager* instance() { static RenderingManager i; return &i; }

    ///
    /// @brief   描画リクエストを登録
    /// @details この関数は描画を行いません。
    ///
    void entry( ... );

    ///
    /// @brief  描画
    /// @detais この関数が呼び出された時点での描画リクエストをすべて解決します。
    ///
    void rendering();

private :
    RenderingManager();

    // 描画リクエストスタック
};
END_EGEG
#endif /// !INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
/// EOF
