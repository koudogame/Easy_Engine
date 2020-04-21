// çÏê¨é“ : î¬èÍ
#include "body3d.hpp"

BEGIN_EGEG
namespace component {
 
/******************************************************************************

	component::SphereBody

******************************************************************************/
bool SphereBody::initialize()
{
    collision_enter_ = nullptr;
    shape_.center = Vector3D{ 0.0F, 0.0F, 0.0F };
    shape_.radius = 0.0F;

    return true;
}
void SphereBody::finalize()
{
    collision_enter_ = nullptr;
}

/******************************************************************************

	component::CuboidBody

******************************************************************************/
bool CuboidBody::initialize()
{
    collision_enter_ = nullptr;
    shape_.center = Vector3D{ 0.0F, 0.0F, 0.0F };
    shape_.width = 0.0F;
    shape_.height = 0.0F;
    shape_.depth = 0.0F;

    return true;
}
void CuboidBody::finalize()
{
    collision_enter_ = nullptr;
}

/******************************************************************************

	component::Line3DBody

******************************************************************************/
bool Line3DBody::initialize()
{
    collision_enter_ = nullptr;
    shape_.start = Vector3D{ 0.0F, 0.0F, 0.0F };
    shape_.distance = Vector3D{ 0.0F, 0.0F, 0.0F };

    return true;
}
void Line3DBody::finalize()
{
    collision_enter_ = nullptr;
}

} // namespace component
END_EGEG
// EOF
