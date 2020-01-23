///
/// @file   sprite.hpp
/// @author 板場
///
/// @brief  スプライトコンポーネント
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_
#include "render_component.hpp"
#include "egeg_math.hpp"
#include "texture.hpp"
#include "model.hpp"
BEGIN_EGEG
class SpriteComponent :
    public RenderComponent
{
public :
    ///
    /// @brief  スプライト情報のセット
    ///
    /// @param[in] pTexture    : 描画するテクスチャ
    /// @param[in] Position    : 描画位置
    /// @param[in] Trimming    : テクスチャ切り取り範囲
    /// @param[in] RotationDEG : 回転角度( 度数法 )
    /// @param[in] Scale       : 拡縮率( x,y各 0.0F ~ 1.0F )
    /// @param[in] Origin      : 原点
    /// @param[in] Color       : カラー値
    /// @param[in] Alpha       : アルファ値
    /// @param[in] Depth       : 深度値( 0.0F ~ 1.0F )
    ///
    void setStatus( ITexture* pTexture,
                    const Vector2D& Position,
                    const Vector4D& Trimming,
                    float RotationDEG = 0.0F,
                    const Vector2D& Scale = Vector2D{ 1.0F, 1.0F },
                    const Vector2D& Origin = Vector2D{ 0.0F, 0.0F },
                    const Vector3D& Color = Vector3D{ 1.0F, 1.0F, 1.0F },
                    float Alpha = 1.0F,
                    float Depth = 0.0F );

// RenderComponent
/*-----------------------------------------------------------------*/
    void render() override;

// IComponent
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

private :
    bool  visible_ = false;
    Model sprite_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
