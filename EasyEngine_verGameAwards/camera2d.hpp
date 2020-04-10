///
/// @file   camera2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CAMERA2D_HEADER_
#define INCLUDED_EGEG_CAMERA2D_HEADER_

#include "camera.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Camera2D
/// @brief  2D��ԏ�̃J����
/// @note   XMMATRIX�Ńr���[�s���\�����ƂɂȂ�̂�2D,3D�𕪂���K�v�͂Ȃ����A�\�����ʋ�����h�����ߊ����ĕ����Ă���B
///
class Camera2D :
    public Camera
{
public :
    ///< ���W���擾
    const Vector2D& getPosition() const noexcept { return position_; }

protected :
    Vector2D position_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA2D_HEADER_
/// EOF
