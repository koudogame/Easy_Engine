///
/// @file   transform2d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_

#include "component.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Transform2DComponent
/// @brief  2D座標変換コンポーネント
///
/// @details 座標はスクリーン座標系で扱われます。 <br>
///          角度は度数法で扱われます。
///
class Transform2DComponent :
    public Component
{
public :
    Transform2DComponent( LevelNode* Owner ) :
        Component{ Owner } {}

    ///
    /// @brief  軸をセット
    ///
    /// @param[in] Pivot : 軸
    ///
    /// @details 軸は原点(左上)からの相対位置です。 <br>
    ///          { 0.0F, 0.0F }で軸と原点が等しくなります。
    ///
    void setPivot( const Vector2D& Pivot ) noexcept { move(); pivot_ = Pivot; }
    ///
    /// @brief  軸を取得
    ///
    /// @return 軸
    ///
    const Vector2D& getPivot() const noexcept { return pivot_; }

    ///
    /// @brief  座標をセット
    ///
    /// @param[in] Position : 座標
    ///
    /// @details スクリーン座標系の値をセットしてください。
    ///
    void setPosition( const Vector2D& Position ) noexcept { move(); position_ = Position; }
    ///
    /// @brief  座標を取得
    ///
    /// @return 座標
    ///
    const Vector2D& getPosition() const noexcept { return position_; }
    
    ///
    /// @brief  回転度をセット
    ///
    /// @param[in] Rotation : 回転度
    ///
    /// @details   度数法の値をセットしてください。
    ///
    void setRotation( const float Rotation ) noexcept { move(); rotation_ = Rotation; }
    ///
    /// @brief  回転度を取得
    ///
    /// @return 回転度
    ///
    float getRotation() const noexcept { return rotation_; }

    ///
    /// @brief  拡大率をセット
    ///
    /// @param[in] Scale : 拡大率
    ///
    /// @details { 1.0F, 1.0F } で各軸に等倍となります。
    ///
    void setScale( const Vector2D& Scale ) noexcept { move(); scale_ = Scale; }
    ///
    /// @brief  拡大率を取得
    ///
    /// @return 拡大率
    ///
    const Vector2D& getScale() const noexcept { return scale_; }

    ///
    /// @brief  ローカル座標変換行列を計算
    ///
    /// @return ローカル座標変換行列
    ///
    const Matrix4x4& calcLocalTransformMatrix() const;
    ///
    /// @brief  グローバル座標変換行列を計算
    ///
    /// @return グローバル座標変換行列
    ///
    Matrix4x4 calcGlobalTransformMatrix() const;

// override
    bool initialize() override;
    void finalize() override;

private :
    void move() noexcept { is_moved_ = true; }

    Vector2D pivot_;
    Vector2D position_;
    float    rotation_;
    Vector2D scale_;
    mutable bool is_moved_;
    mutable Matrix4x4 transform_cache_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
/// EOF
