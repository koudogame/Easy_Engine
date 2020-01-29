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
    SpriteComponent( Actor* Owner );

    ///
    /// @brief  スプライト情報のセット
    ///
    /// @param[in] pTexture    : テクスチャ
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
                    const Vector3D& Color = Vector3D{ 0.0F, 0.0F, 0.0F },
                    float Alpha = 1.0F,
                    float Depth = 0.0F );
    ///
    /// @brief  テクスチャのセット
    ///
    /// @param[in] pTexture : テクスチャ
    ///
    void setTexture( ITexture* pTexture );
    ///
    /// @brief  描画座標のセット
    ///
    /// @param[in] Position : 座標
    ///
    void setPosition( const Vector2D& Position ) { position_ = Position; }
    ///
    /// @brief  テクスチャ切り取り範囲のセット
    ///
    /// @param[in] Trimming : 切り取り範囲
    ///
    void setTrimming( const Vector4D& Trimming ) { trimming_ = Trimming; }
    ///
    /// @brief   転角のセット
    ///
    void setRotation( float RotationDEG ) { rotation_ = RotationDEG; }
    ///
    /// @brief  拡縮率のセット
    ///
    /// @param[in] Scale : 拡縮率
    ///
    void setScale( const Vector2D& Scale ) { scale_ = Scale; }
    ///
    /// @brief   原点のセット
    /// @details { 0.0F, 0.0F }を画像の左上としたときの相対座標です。
    ///
    /// @param[in] Origin : 原点
    ///
    void setOrigin( const Vector2D& Origin ) { origin_ = Origin; }
    ///
    /// @brief   カラーのセット
    /// @details 各色 0.0F ~ 1.0F の範囲内で設定して下さい。
    ///
    /// @param[in] Color : 色{ R, G, B }
    ///
    void setColor( const Vector3D& Color ) { color_.x = Color.x; color_.y = Color.y; color_.z = Color.z; }
    ///
    /// @brief   カラーのセット
    /// @details 各色 0.0F ~ 1.0F の範囲で設定して下さい。
    ///
    /// @param[in] Color : 色{ R, G, B, A }
    ///
    void setColor( const Vector4D& Color ) { color_ = Color; }
    ///
    /// @brief  アルファ値のセット
    ///
    /// @param[in] Alpha : アルファ値( 0.0F ~ 1.0F )
    ///
    void setAlpha( float Alpha ) { color_.w = Alpha; }
    ///
    /// @brief  深度値のセット
    ///
    /// @param[in] Depth : 深度値( 0.0F ~ 1.0F )
    ///
    void setDepth( float Depth ) { depth_ = Depth; }
        
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize() override;
/*-----------------------------------------------------------------*/
private :
/*-----------------------------------------------------------------*/
// RenderComponent
    void render() override;             /// 通常RenderBatch以外からの呼び出しを禁止しています。
/*-----------------------------------------------------------------*/
    void getModelStatus( Model* );
    void getVerticesPositoin( Vector3D* );
    void getVerticesUV( Vector2D* );

    bool  is_validity_ = false;         /// 有効状態判定フラグ
    ITexture* p_texture_ = nullptr;     /// テクスチャ
    Vector2D  position_;                /// 描画座標
    Vector4D  trimming_;                /// テクスチャ切り取り範囲
    float     rotation_;                /// 回転角(度数法)
    Vector2D  scale_;                   /// 拡縮率
    Vector2D  origin_;                  /// 原点
    Vector4D  color_;                   /// 色情報
    float     depth_;                   /// 深度値
    IVertexShader* p_vertex_shader_;    /// 頂点シェーダ―
    IPixelShader*  p_pixel_shader_;     /// ピクセルシェーダー
};
END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
