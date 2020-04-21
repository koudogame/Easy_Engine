///
/// @file   focused_camera.hpp
/// @author 板場
///
#ifndef INCLUDED_FOCUSED_CAMERA_HEADER_
#define INCLUDED_FOCUSED_CAMERA_HEADER_

#include "camera3d.hpp"
#include "egeg_math.hpp"

///
/// @class  FocusedCamera
/// @brief  焦点を持つカメラ
///
class FocusedCamera :
    public EGEG Camera3D
{
public :
    ///
    /// @brief  焦点の座標をセット
    ///
    void setFocusPoint( const EGEG Vector3D& FocusPoint ) noexcept { focus_ = FocusPoint; }
    ///
    /// @brief  焦点の座標を取得
    ///
    const EGEG Vector3D& getFocusPoint() const noexcept { return focus_; }

    // overrides
    DirectX::FXMMATRIX calcViewMatrix() const
    {
        return DirectX::XMMatrixLookAtLH(
            position_,
            focus_,
            {0.0F, 1.0F, 0.0F, 0.0F }
        );
    }

private :
    EGEG Vector3D focus_;
};

#endif /// !INCLUDED_FOCUSED_CAMERA_HEADER_
/// EOF
