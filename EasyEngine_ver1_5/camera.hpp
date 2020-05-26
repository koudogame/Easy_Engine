///
/// @file   camera.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CAMERA_HEADER_
#define INCLUDED_EGEG_CAMERA_HEADER_

#include <DirectXMath.h>
#include "actor3d.hpp"

BEGIN_EGEG

///
/// @class Camera
/// @brief カメラ
///
class Camera :
    public Actor3D
{
public :
    explicit Camera( uint32_t ID ) : Actor3D{ ID } {}
    virtual ~Camera() = default;

    ///
    /// @brief ビュー変換行列を計算
    ///
    /// @return ビュー変換行列
    ///
    virtual DirectX::XMMATRIX calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA_HEADER_
/// EOF
