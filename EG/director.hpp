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
BEGIN_EGEG
class Director
{
public :
    ~Director();

    ///
    /// @brief   初期化処理
    /// @details 必ず最初に呼び出してください。
    ///
    /// @param[in] Platform : 使用するプラットフォーム識別ID
    ///
    /// @return 初期化に成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool initialize( PlatformID Platform );

    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static Director* instance() { static Director i; return &i; }

    ///
    /// @brief   採用しているプラットフォームを取得します。
    /// @details addRef関数の呼び出しは行っていません。
    ///
    /// @return プラットフォームのアドレス
    ///
    IPlatform* getPlatform() const { return p_platform_; }
    ///
    /// @brief   レンダラーを取得します。
    /// @details addRef関数の呼び出しは行っていません。
    ///
    /// @return レンダラーのアドレス
    ///
    IRenderer* getRenderer() const { return p_platform_->getRenderer(); }
    ///
    /// @brief   シェーダーローダーを取得します。
    /// @details addRef関数の呼び出しは行っていません。
    ///
    /// @return シェーダーローダーのアドレス
    ///
    //IShaderLoader* getShaderLoader() const { return p_platform_->getShaderLoader(); }
    ///
    /// @brief   テクスチャローダーを取得します。
    /// @details addRef関数の呼び出しは行っていません。
    ///
    /// @return テクスチャローダーのアドレス 
    ///
    ITextureLoader* getTextureLoader() const { return p_platform_->getTextureLoader(); }

private :
    Director();

    IPlatform* p_platform_; /// 生成したプラットフォームを格納
};
END_EGEG
#endif /// !INCLUDED_EG_EG_DIRECTOR_HEADER_
/// EOF
