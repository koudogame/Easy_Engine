///
/// @file   camera_3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CAMERA3D_HEADER_
#define INCLUDED_EGEG_CAMERA3D_HEADER_

#include "camera.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Camera3D
/// @brief  3D空間上のカメラ
/// @note   XMMATRIXでビュー行列を表すことになるので2D,3Dを分ける必要はないが、予期せぬ挙動を防ぐため敢えて分けている。
///
class Camera3D :
    public Camera
{
public :
    ///< 座標をセット
    void setPosition( const Vector3D& Destination ) noexcept { position_ = Destination; }

    ///< 座標を取得
    const Vector3D& getPosition() const noexcept { return position_; }

protected :
    Vector3D position_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA3D_HEADER_
/// EOF
