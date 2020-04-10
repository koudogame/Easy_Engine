///
/// @file   camera.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CAMERA_HEADER_
#define INCLUDED_EGEG_CAMERA_HEADER_

#include <DirectXMath.h>
#include "egeg.hpp"

BEGIN_EGEG
///
/// @class  Camera
/// @brief  カメラ
///
class Camera
{
public :
    ///< 仮想デストラクタ
    virtual ~Camera() = default;

    ///< ビュー変換行列を計算して返却
    virtual DirectX::FXMMATRIX calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA_HEADER_
/// EOF
