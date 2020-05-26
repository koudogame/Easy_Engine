///
/// @file   camera.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CAMERA_HEADER_
#define INCLUDED_EGEG_CAMERA_HEADER_

#include <DirectXMath.h>
#include "actor3d.hpp"

BEGIN_EGEG

///
/// @class Camera
/// @brief �J����
///
class Camera :
    public Actor3D
{
public :
    explicit Camera( uint32_t ID ) : Actor3D{ ID } {}
    virtual ~Camera() = default;

    ///
    /// @brief �r���[�ϊ��s����v�Z
    ///
    /// @return �r���[�ϊ��s��
    ///
    virtual DirectX::XMMATRIX calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA_HEADER_
/// EOF
