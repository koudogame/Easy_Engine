///
/// @file   focused_camera.hpp
/// @author ��
///
#ifndef INCLUDED_FOCUSED_CAMERA_HEADER_
#define INCLUDED_FOCUSED_CAMERA_HEADER_

#include "camera3d.hpp"
#include "egeg_math.hpp"

///
/// @class  FocusedCamera
/// @brief  �œ_�����J����
///
class FocusedCamera :
    public EGEG Camera3D
{
public :
    ///
    /// @brief  �œ_�̍��W���Z�b�g
    ///
    void setFocusPoint( const EGEG Vector3D& FocusPoint ) noexcept { focus_ = FocusPoint; }
    ///
    /// @brief  �œ_�̍��W���擾
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
