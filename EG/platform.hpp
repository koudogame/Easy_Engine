///
/// @file    platform.hpp
/// @author  板場
///          
/// @brief   プラットフォームインターフェイス
/// @details PlatformFactoryにより提供されます。<br>
///          新しいプラットフォームを作成する際、PlatformFactoryへの登録を必ず行ってください。<br>
///          登録時に識別IDを使用するので、PlatformIDに識別IDを追加してください。
///
#ifndef INCLUDED_EG_EG_PLATFORM_HEADER_
#define INCLUDED_EG_EG_PLATFORM_HEADER_
#include <functional>
#include "interface.hpp"
#include "renderer.hpp"
#include "texture_loader.hpp"
#include "shader_factory.hpp"
BEGIN_EGEG
///
/// @enum   PlatformID
/// @brief  プラットフォームを識別するIDです。
///
enum PlatformID
{
    kWindows,
    kNintendoSwitch,
};

class IPlatform :
    public Interface
{
public :
// プラットフォーム依存の機能
/*-----------------------------------------------------------------*/
    ///
    /// @brief   ゲームループ
    /// @details 引数の関数について<br>
    ///          引数には呼び出し毎の経過時間(: ミリ秒)を与えます。<br>
    ///          戻り値で[ false ]が返ってきた場合、ループを終了します。
    ///
    /// @param[in]  pUpdateFunc : 毎ループ呼び出す関数へのポインタ
    ///
    virtual void gameLoop( std::function<bool(long long)> pUpdateFunc ) = 0;

    ///
    /// @brief  ダイアログボックスの表示
    ///
    /// @param[in]  Message : ダイアログボックスに表示する文字列
    ///
    virtual void showDialogBox( const char Message[] ) = 0;
    
// 各種インターフェイスの取得
/*-----------------------------------------------------------------*/
    ///
    ///@brief   レンダラーの取得
    ///
    /// @return レンダラーのアドレス
    ///
    virtual IRenderer* getRenderer() const = 0;
    ///
    /// @brief  テクスチャローダーの取得
    ///
    /// @return テクスチャローダー
    ///
    virtual ITextureLoader* getTextureLoader() const = 0;
    ///
    /// @brief  シェーダーファクトリの取得
    ///
    /// @return シェーダーファクトリ
    ///
    virtual IShaderFactory* getShaderLoader() const = 0;

protected :
    IPlatform() = default;
    virtual ~IPlatform() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_PLATFORM_HEADER_
/// EOF
