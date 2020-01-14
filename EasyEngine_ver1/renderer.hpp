///
/// @file   renderer.hpp
/// @author 板場
///
/// @brief  レンダラー
///
#ifndef INCLUDED_EGEG_RENDERER_HEADER_
#define INCLUDED_EGEG_RENDERER_HEADER_
#include "interface.hpp"
#include "model.hpp"
BEGIN_EGEG
class IRenderer :
    public Interface
{
public :
    ///
    /// @brief   描画開始
    /// @details 引数のカラー情報は、各色0.0F ~ 1.0Fで設定してください。
    ///
    /// @param[in] ColorRGBA : 画面のクリア色 { R, G, B, A }
    ///
    virtual void beginRender( const Vector4D& Color ) = 0;
    ///
    /// @brief   描画のエントリー
    /// @details 実際に描画は行いません。
    ///
    /// @param[in] Model : 描画するモデル
    ///
    virtual void entryRender( const Model& Model ) = 0;
    ///
    /// @brief   描画終了
    /// @details beginRenderの呼び出しから、<br>
    ///          この関数が呼び出されるまでにエントリーされたモデルを描画します。
    ///
    virtual void endRender() = 0;

protected :
    virtual ~IRenderer() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_HEADER_
/// EOF
