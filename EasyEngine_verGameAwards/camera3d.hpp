///
/// @file   camera_3d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_CAMERA3D_HEADER_
#define INCLUDED_EGEG_CAMERA3D_HEADER_

#include "camera.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Camera3D
/// @brief  3D��ԏ�̃J����
/// @note   XMMATRIX�Ńr���[�s���\�����ƂɂȂ�̂�2D,3D�𕪂���K�v�͂Ȃ����A�\�����ʋ�����h�����ߊ����ĕ����Ă���B
///
class Camera3D :
    public Camera
{
public :
    ///< ���W���Z�b�g
    void setPosition( const Vector3D& Destination ) noexcept { position_ = Destination; }

    ///< ���W���擾
    const Vector3D& getPosition() const noexcept { return position_; }

protected :
    Vector3D position_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_CAMERA3D_HEADER_
/// EOF
