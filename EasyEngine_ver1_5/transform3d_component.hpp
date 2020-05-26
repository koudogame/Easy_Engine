///
/// @file   transform3d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_

#include "component3d.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class Transform3DComponent
/// @brief 3Dアクター用座標変換コンポーネント
///
class Transform3DComponent :
    public Component3D
{
public :
    Transform3DComponent( Actor3D* Owner ) :
        Component3D{ Owner }
    {}

    ///
    /// @brief 座標のセット
    ///
    /// @param[in] Position
    ///
    void setPosition( const Vector3D& Position ) noexcept { position_ = Position; }
    ///
    /// @brief 座標の取得
    ///
    /// @return 座標
    ///
    const Vector3D& getPosition() const noexcept { return position_; }

    ///
    /// @brief 回転角のセット
    ///
    /// @param[in] RotationDeg : 回転角( 各軸度数法 )
    ///
    void setRotationDeg( const Vector3D& RotationDeg ) noexcept { rotation_deg_ = RotationDeg; }
    ///
    /// @brief 回転角の取得
    ///
    /// @return 回転角( 各軸度数法 )
    ///
    const Vector3D& getRotationDeg() const noexcept { return rotation_deg_; }

    ///
    /// @brief  拡縮率のセット
    ///
    /// @param[in] Scale : 拡縮率
    ///
    void setScale( const Vector3D& Scale ) noexcept { scale_ = Scale; }
    ///
    /// @brief 拡縮率の取得
    ///
    /// @return 拡縮率
    ///
    const Vector3D& getScale() const noexcept { return scale_; }

// override
    bool initialize() override;
    void finalize() override;
private :
    Vector3D position_;
    Vector3D rotation_deg_;
    Vector3D scale_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
