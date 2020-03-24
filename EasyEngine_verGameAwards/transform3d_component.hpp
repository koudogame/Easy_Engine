///
/// @file   transform3d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#include "component.hpp"
#include "egeg_math.hpp"
#include "actor3d.hpp"
#include "uid.hpp"
BEGIN_EGEG
///
/// @class  Transform3DComponent
/// @brief  ワールド座標の管理コンポーネント
///
class Transform3DComponent :
    public Component
{
public :
    static constexpr UID<Transform3DComponent> getID() noexcept { return UID<Transform3DComponent>(); }

    Transform3DComponent( Actor3D* Owner ) :
        Component( Owner )
    {}

    ///< 座標のセット
    void setPosition( const Vector3D& Destination ) noexcept { position_ = Destination; }
    ///< 座標の取得
    const Vector3D& getPosition() const noexcept { return position_; }

    ///< 拡縮率のセット
    void setScale( const Vector3D& Scale ) noexcept { scale_ = Scale; }
    ///< 拡縮率の取得
    const Vector3D& getScale() const noexcept { return scale_; }

    ///< 回転度数のセット
    void setRotation( const Vector3D& Rotation ) noexcept { rotation_ = Rotation; }
    ///< 回転度数の取得
    const Vector3D& getRotation() const noexcept { return rotation_; }
        
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize() override;
/*-----------------------------------------------------------------*/
private :
    Vector3D position_;
    Vector3D scale_;
    Vector3D rotation_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
