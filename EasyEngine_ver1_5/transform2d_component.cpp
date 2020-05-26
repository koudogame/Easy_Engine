// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "transform2d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Transform2DComponent

******************************************************************************/
 // 初期化
bool Transform2DComponent::initialize()
{
    pivot_              = Vector2D{ 0.0F, 0.0F };
    position_           = Vector2D{ 0.0F, 0.0F };
    rotation_angle_deg_ = 0.0F;
    scale_              = Vector2D{ 1.0F, 1.0F };

    return true;
}


 // 終了
void Transform2DComponent::finalize()
{
    
}

END_EGEG
// EOF
