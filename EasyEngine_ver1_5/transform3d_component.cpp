// çÏê¨é“ : î¬èÍ
/******************************************************************************

	include

******************************************************************************/
#include "transform3d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Transform3DComponent

******************************************************************************/
 // èâä˙âª
bool Transform3DComponent::initialize()
{
	position_     = Vector3D{ 0.0F, 0.0F, 0.0F };
	rotation_deg_ = Vector3D{ 0.0F, 0.0F, 0.0F };
	scale_        = Vector3D{ 1.0F, 1.0F, 1.0F };
	return true;
}


 // èIóπèàóù
void Transform3DComponent::finalize()
{

}

END_EGEG
// EOF
