///
/// @file   platform.hpp
/// @author 板場
///
/// @brief  プラットフォーム
///
#ifndef INCLUDED_EGEG_PLATFORM_HEADER_
#define INCLUDED_EGEG_PLATFORM_HEADER_
#include <functional>
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class IPlatform
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
    virtual void mainLoop( std::function<bool(uint64_t)> pUpdateFunction ) = 0;

    ///
    /// @brief  ダイアログボックスの表示
    ///
    /// @param[in] Message : ダイアログボックスに表示する文字列
    ///
    virtual void showDialogBox( const std::string& Message ) = 0;

    ///
    /// @brief   レンダラーの生成
    ///
    /// @param[out] ppRenderer : 生成したレンダラーを格納するインターフェイス
    ///
    /// @return 生成に成功[ true ] 生成に失敗[ false ]
    ///
    virtual bool createRenderer( IRenderer** ppRenderer ) = 0;
    ///
    /// @brief   シェーダーローダーの生成
    ///    
    /// @param[out] ppShaderLoader : 生成したシェーダーローダーを格納するインターフェイス
    ///
    /// @return 生成に成功[ true ] 生成に失敗[ false ]
    ///
    virtual bool createShaderLoader( IShaderLoader** ppShaderLoader ) = 0;
    ///
    /// @brief   テクスチャローダーの生成
    ///
    /// @param[out] ppTextureLoader : 生成したテクスチャローダーを格納するインターフェイス
    ///
    /// @return 生成に成功[ true ] 生成に失敗[ false ]
    ///
    virtual bool createTextureLoader( ITextureLoader** ppTextureLoader ) = 0;

    virtual ~IPlatform() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_HEADER_
/// EOF
