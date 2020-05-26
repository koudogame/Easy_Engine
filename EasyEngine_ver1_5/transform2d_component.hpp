///
/// @file   transform2d_component.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_

#include "component2d.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class Transform2DComponent
/// @brief 2Dアクター用座標変換コンポーネント
///
class Transform2DComponent :
    public Component2D
{
public :
    Transform2DComponent( Actor2D* Owner ) :
        Component2D{ Owner }
    {}

    ///
    /// @brief  中心のセット
    ///
    /// @param[in] Pivot : 中心
    ///
    /// @details 座標( Position )からの相対座標
    ///
    void setPivot( const Vector2D& Pivot ) noexcept { pivot_ = Pivot; }
    ///
    /// @brief  中心の取得
    ///
    /// @return 中心
    ///
    const Vector2D& getPivot() const noexcept { return pivot_; }

    ///
    /// @brief 座標のセット
    ///
    /// @param[in] Position : 座標
    ///
    /// @details 左上が基点
    ///
    void setPosition( const Vector2D& Position ) noexcept { position_ = Position; }
    ///
    /// @brief 座標の取得
    ///
    /// @return 座標
    ///
    const Vector2D& getPosition() const noexcept { return position_; }

    ///
    /// @brief 回転角度のセット
    ///
    /// @param[in] RotationDeg : 回転角( 度数法 )
    ///
    void setRotationDeg( float RotationDeg ) noexcept { rotation_angle_deg_ = RotationDeg; }
    ///
    /// @brief 回転角度の取得
    ///
    /// @return 回転角度( 度数法 )
    ///
    float getRotationDeg() const noexcept { return rotation_angle_deg_; }

    ///
    /// @brief 拡縮率のセット
    ///
    /// @param[in] Scale : 拡縮率
    ///
    void setScale( const Vector2D& Scale ) noexcept { scale_ = Scale; }
    ///
    /// @brief 拡縮率の取得
    ///
    /// @return 拡縮率
    ///
    const Vector2D& getScale() const noexcept { return scale_; }

// override
    bool initialize() override;
    void finalize() override;
private :
    Vector2D pivot_;
    Vector2D position_;
    float rotation_angle_deg_;
    Vector2D scale_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
/// EOF
