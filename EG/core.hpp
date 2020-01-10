///
/// @file    core.hpp
/// @author  板場
///          
/// @brief   中核クラス
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
#ifndef INCLUDED_EG_EG_CORE_HEADER_
#define INCLUDED_EG_EG_CORE_HEADER_
#include "easy_engine.hpp"
#include "platform.hpp"
BEGIN_EG_EG
class Core
{
public :
    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static Core* instance() { static Core i; return &i; }

    ///
    /// @brief  プラットフォームを取得します。
    ///
    /// @return プラットフォームのアドレス
    ///
    IPlatform* getPlatform() const { return p_platform_; }

    ///
    /// @brief   初期化処理
    ///
    /// @param[in] Platform : ターゲットプラットフォーム
    ///
    /// @return 初期化に成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool initialize( PlatformID TargetPlatform );

    ///
    /// @brief  終了処理
    ///
    void finalize();

private :
    Core() = default;

    IPlatform* p_platform_ = nullptr;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_CORE_HEADER_
/// EOF
