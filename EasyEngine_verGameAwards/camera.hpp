///
/// @file   camera.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CAMERA_HEADER_
#define INCLUDED_EGEG_CAMERA_HEADER_

#include <DirectXMath.h>
#include "egeg.hpp"

BEGIN_EGEG
///
/// @class  Camera
/// @brief  �J����
///
class Camera
{
public :
    ///< ���z�f�X�g���N�^
    virtual ~Camera() = default;

    ///< �r���[�ϊ��s����v�Z���ĕԋp
    virtual DirectX::FXMMATRIX calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA_HEADER_
/// EOF
