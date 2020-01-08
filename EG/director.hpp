///
/// @file    director.hpp
/// @author  板場
///          
/// @brief   ゲーム全体統括クラス
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
#ifndef INCLUDED_EG_EG_DIRECTOR_HEADER_
#define INCLUDED_EG_EG_DIRECTOR_HEADER_
#include "platform.hpp"
#include "renderer.hpp"
BEGIN_EG_EG
class Director
{
public :
    ~Director();

    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static Director* instance() { static Director i; return &i; }

    ///
    /// @brief  採用しているプラットフォームを取得します。
    ///
    /// @return インターフェイス
    ///
    IPlatform* getPlatform() const { return p_platform_; }
    ///
    /// @brief  採用しているレンダラーを取得します。
    ///
    /// @return インターフェイス
    ///
    IRenderer* getRenderer() const { return p_renderer_; }

    ///
    /// @brief   初期化処理
    /// @details 必ず最初に呼び出してください。
    ///
    /// @param[in] Platform : 使用するプラットフォーム識別ID
    /// @param[in] Renderer : 使用するレンダラー識別ID
    ///
    /// @return 初期化に成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool initialize( PlatformID Platform, RendererID Renderer );

private :
    Director();

    IPlatform* p_platform_; /// 生成したプラットフォームを格納
    IRenderer* p_renderer_; /// 生成したレンダラーを格納
};
END_EG_EG
#endif /// INCLUDED_EG_EG_DIRECTOR_HEADER_
/// EOF
