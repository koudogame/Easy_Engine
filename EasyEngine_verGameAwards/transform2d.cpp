// �쐬�� : ��
#include "transform2d.hpp"

BEGIN_EGEG
namespace component {

// Transform2D �֐���`
/*===========================================================================*/
// ������
bool Transform2D::initialize()
{
    position_ = Vector2D( 0.0F, 0.0F );
    scale_    = Vector2D( 1.0F, 1.0F );
    rotation_ = 0.0F;

    return true;
}

// �I��
void Transform2D::finalize()
{

}

} // namespace component
END_EGEG
// EOF
