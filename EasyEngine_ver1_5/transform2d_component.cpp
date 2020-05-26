// çÏê¨é“ : î¬èÍ
/******************************************************************************

	include

******************************************************************************/
#include "transform2d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Transform2DComponent

******************************************************************************/
 // èâä˙âª
bool Transform2DComponent::initialize()
{
    pivot_              = Vector2D{ 0.0F, 0.0F };
    position_           = Vector2D{ 0.0F, 0.0F };
    rotation_angle_deg_ = 0.0F;
    scale_              = Vector2D{ 1.0F, 1.0F };

    return true;
}


 // èIóπ
void Transform2DComponent::finalize()
{
    
}

END_EGEG
// EOF
