///
/// @file   camera2d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CAMERA2D_HEADER_
#define INCLUDED_EGEG_CAMERA2D_HEADER_

#include "camera.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Camera2D
/// @brief  2D空間上のカメラ
/// @note   XMMATRIXでビュー行列を表すことになるので2D,3Dを分ける必要はないが、予期せぬ挙動を防ぐため敢えて分けている。
///
class Camera2D :
    public Camera
{
public :
    ///< 座標を取得
    const Vector2D& getPosition() const noexcept { return position_; }

protected :
    Vector2D position_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA2D_HEADER_
/// EOF
