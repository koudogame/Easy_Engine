// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "transform2d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Transform2DComponent

******************************************************************************/
 // ������
bool Transform2DComponent::initialize()
{
    pivot_              = Vector2D{ 0.0F, 0.0F };
    position_           = Vector2D{ 0.0F, 0.0F };
    rotation_angle_deg_ = 0.0F;
    scale_              = Vector2D{ 1.0F, 1.0F };

    return true;
}


 // �I��
void Transform2DComponent::finalize()
{
    
}

END_EGEG
// EOF
