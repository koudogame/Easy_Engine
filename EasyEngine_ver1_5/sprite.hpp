///
/// @file   sprite.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_

#include "actor2d.hpp"
#include "egeg_math.hpp"
#include "task.hpp"
#include "mesh.hpp"
#include "shader.hpp"

BEGIN_EGEG

///
/// @class  Sprite
/// @brief  スプライト、画像
///
/// @details 初期化時にストリームから受け取るデータは <br>
///           std::string : 読み込む画像ファイルパス <br>
///                                         　です。
///
class Sprite :
    public Actor2D
{
public :
    Sprite() : Actor2D{ TypeID<Sprite>{} }
    {}

    ///
    /// @brief 切り取り範囲の基点をセット
    ///
    /// @param[in] BasePoint : 基点
    ///
    void setTrimmingBasePoint( const Vector2D& BasePoint ) noexcept { trim_base_point_ = BasePoint; }
    ///
    /// @brief 切り取り範囲の基底を取得
    ///
    /// @return 基点
    ///
    const Vector2D& getTrimmingBasePoint() const noexcept { return trim_base_point_; }

    ///
    /// @brief 横幅をセット
    ///
    /// @param[in] Width : 横幅
    ///
    void setWidth( float Width ) noexcept { width_ = Width; }
    ///
    /// @brief 横幅を取得
    ///
    /// @return 横幅
    ///
    float getWidth() const noexcept { return width_; }

    ///
    /// @brief 縦幅をセット
    ///
    /// @param[in] Height : 縦幅
    ///
    void setHeight( float Height ) noexcept { height_ = Height; }
    ///
    /// @brief 縦幅を取得
    ///
    /// @return 縦幅
    ///
    float getHeight() const noexcept { return height_; }

    ///
    /// @brief 更新
    ///
    void update( uint64_t );

// override
    bool initialize( std::istream& ) override;
    void finalize() override;
    DirectX::XMMATRIX calcWorldMatrix() const override;

private :
    bool createMesh();
    bool loadTexture( const std::string& );
    void initComponent();
    void registerTask();

    Task task_;
    Mesh mesh_;
    std::unique_ptr<IShader> shader_;
    Vector2D trim_base_point_;
    float width_ = 0.0F;
    float height_= 0.0F;
    float texture_width_ = 0.0F;
    float texture_height_= 0.0F;
};

REGISTER_ACTOR( Sprite, Sprite );

END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
