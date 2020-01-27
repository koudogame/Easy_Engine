///
/// @file   renderer.hpp
/// @author 板場
///
/// @brief  レンダラー
///
#ifndef INCLUDED_EGEG_RENDERER_HEADER_
#define INCLUDED_EGEG_RENDERER_HEADER_
#include "model.hpp"
BEGIN_EGEG
class IRenderer
{
public :
    ///
    /// @enum   BlendMode
    /// @brief  合成モード
    ///
    enum BlendMode
    {
        kNormal,        ///< 通常モード *描画色をそのまま描画
        kAdditive,      ///< 加算モード *元の色と描画色を加算した色を描画
        kSubtraction,   ///< 減算モード *元の色から描画色を減算した色を描画
    };

    ///
    /// @brief  描画対象画面のサイズ取得
    ///
    /// @return 描画対象画面サイズ
    ///
    virtual Vector2D getScreenSize() const = 0;

    ///
    /// @brief  画面クリア
    /// @details 引数のカラー情報は、各色0.0F ~ 1.0Fで設定してください。
    ///
    /// @param[in] ColorRGBA : クリア色 { R, G, B, A }
    ///
    virtual void clear( const Vector4D& ColorRGBA ) = 0;

    ///
    /// @brief  描画開始
    ///
    virtual void beginRender() = 0;

    ///
    /// @brief  モデルの描画
    ///
    /// @param[in] Model : 描画するモデル
    /// @param[in] Mode  : 描画モード
    ///
    virtual void renderModel( const Model& Model, BlendMode Mode = BlendMode::kNormal ) = 0;

    ///
    /// @brief  描画終了
    ///
    virtual void endRender() = 0;


    virtual ~IRenderer() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_HEADER_
/// EOF
