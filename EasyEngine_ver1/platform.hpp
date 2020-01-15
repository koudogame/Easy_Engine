///
/// @file   platform.hpp
/// @author 板場
///
/// @brief  プラットフォーム
///
#ifndef INCLUDED_EGEG_PLATFORM_HEADER_
#define INCLUDED_EGEG_PLATFORM_HEADER_
#include <functional>
#include "interface.hpp"
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class IPlatform :
    public Interface
{
public :
    ///
    /// @brief   メインループ
    /// @details 引数の関数について<br>
    ///          引数には呼び出し毎の経過時間(: ミリ秒)を与えます。<br>
    ///          戻り値で[ false ] が返ってきた場合、ループを終了します。
    ///
    /// @param[in] pUpdateFunction : ループ中に実行するゲームの更新関数
    ///
    virtual void MainLoop( std::function<bool(long long)> pUpdateFunction ) = 0;

    ///
    /// @brief  ダイアログボックスの表示
    ///
    /// @param[in] Message : ダイアログボックスに表示する文字列
    ///
    virtual void showDialogBox( const wchar_t* Message ) = 0;

    ///
    /// @brief   レンダラーの取得
    ///
    /// @return  レンダラーのアドレス
    ///
    virtual IRenderer* getRenderer() const = 0;
    ///
    /// @brief   シェーダーローダーの取得
    ///
    /// @return  シェーダーローダーのアドレス
    ///
    virtual IShaderLoader* getShaderLoader() const = 0;
    ///
    /// @brief   テクスチャローダーの取得
    ///
    /// @return  テクスチャローダーのアドレス
    ///
    virtual ITextureLoader* getTextureLoader() const = 0;

protected :
    virtual ~IPlatform() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_HEADER_
/// EOF
