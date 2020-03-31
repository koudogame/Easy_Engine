///
/// @file   camera.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_CAMERA_HEADER_
#define INCLUDED_EGEG_CAMERA_HEADER_
#include <DirectXMath.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  Camera
/// @brief  ÉJÉÅÉâ
///
class Camera
{
public :
    virtual ~Camera() = default;

    virtual DirectX::FXMMATRIX getViewMatrix() const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA_HEADER_
/// EOF
