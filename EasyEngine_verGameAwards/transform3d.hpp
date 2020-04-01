///
/// @file   transform3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#include "component3d.hpp"
#include "egeg_math.hpp"
#include "uid.hpp"

BEGIN_EGEG
namespace component {

///
/// @class  Transform3D
/// @brief  ワールド座標の管理コンポーネント
///
class Transform3D :
    public Component3D
{
public :
    static constexpr UID<Transform3D> getID() noexcept { return UID<Transform3D>(); }

    Transform3D( Actor3D* Owner ) :
        Component3D( Owner )
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

} /// namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
