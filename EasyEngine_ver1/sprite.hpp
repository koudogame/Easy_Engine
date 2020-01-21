///
/// @file    sprite.hpp
/// @author  板場
///          
/// @brief   スプライト
/// @details 2Dテクスチャの描画を行います。
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_
#include "rendering_manager.hpp"
BEGIN_EGEG
class Sprite
{
public :
    ///
    /// @brief  初期化処理
    ///
    /// @param[in] TextureFileName : 読み込むテクスチャのファイル(パス)名
    ///
    /// @return 初期化成功[ true ] 初期化失敗[ false ]
    ///
    bool initialize( const std::wstring& TextureFileName );
    ///
    /// @brief  終了処理
    ///
    void finalize();

    ///
    /// @brief  画像の描画
    ///
    /// @param[in] Position : 表示座標
    /// @param[in] Trimming : 画像切り取り範囲
    /// @param[in] Alpha    : 表示α値 *0.0F ~ 1.0Fの間*
    /// @param[in] Rotation : 回転角度( 度数法 )
    /// @param[in] Scale    : 拡大率
    /// @param[in] Origin   : 原点 *左上からの相対位置*
    ///
    void draw(
        const Vector2D& Position,
        const Vector4D& Trimming,
        float Alpha = 1.0F,
        float Rotation = 0.0F,
        const Vector2D& Scale = { 1.0F, 1.0F },
        const Vector2D& Origin = { 0.0F, 0.0F }
    );

private :
    ITexture* texture_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
