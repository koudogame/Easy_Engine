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
    /// @brief  モデルの描画
    ///
    /// @param[in] Model : 描画するモデル
    ///
    virtual void renderModel( const Model& Model ) = 0;


    virtual ~IRenderer() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_HEADER_
/// EOF
