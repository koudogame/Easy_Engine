///
/// @file   transform3d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_

#include "component.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Transform3DComponent
/// @brief  3D座標変換コンポーネント
///
/// @details 3D座標系で扱われます。 <br>
///          回転角は度数法で扱われます。
///
class Transform3DComponent :
    public Component
{
public :
    Transform3DComponent( LevelNode* Owner ) :
        Component{ Owner } {}

    ///
    /// @brief  座標をセット
    ///
    /// @param[in] Position : 座標
    ///
    void setPosition( const Vector3D& Position ) noexcept { move(); position_ = Position; }
    ///
    /// @brief  座標を取得
    ///
    /// @return 座標
    ///
    const Vector3D& getPosition() const noexcept { return position_; }

    ///
    /// @brief  各軸の回転角を設定
    ///
    /// @param[in] Rotation : 各軸の回転角
    ///
    ///
    void setRotation( const Vector3D& Rotation ) noexcept { move(); rotation_ = Rotation; }
    ///
    /// @brief  各軸の回転角を取得
    ///
    /// @return 各軸の回転角
    ///
    const Vector3D& getRotation() const noexcept { return rotation_; }

    ///
    /// @brief  拡大率を設定
    ///
    /// @param[in] Scale : 拡大率
    ///
    /// @details { 1.0F, 1.0F, 1.0F } で各軸に等倍となります。
    ///
    void setScale( const Vector3D& Scale ) noexcept { move(); scale_ = Scale; }
    ///
    /// @brief  拡大率を取得
    ///
    /// @return 拡大率
    ///
    const Vector3D& getScale() const noexcept { return scale_; }

    ///
    /// @brief  ローカル変換座標を計算
    ///
    /// @return ローカル座標行列
    ///
    const Matrix4x4& calcLocalTransformMatrix() const;
    ///
    /// @brief  ワールド変換行列を計算
    ///
    /// @return ワールド変換行列
    ///
    Matrix4x4 calcGlobalTransformMatrix() const;

// override
    bool initialize() override;
    void finalize() override;

private :
    void move() noexcept { is_moved_ = true; }

    Vector3D position_;
    Vector3D rotation_;
    Vector3D scale_;
    mutable bool is_moved_;
    mutable Matrix4x4 transform_cache_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
