// ì¬Ò : ”Âê
#include "transform3d.hpp"

BEGIN_EGEG
namespace component {

// Transform3D ŠÖ”’è‹`
/*===========================================================================*/
// ‰Šú‰»
bool Transform3D::initialize()
{
    position_ = Vector3D{ 0.0F, 0.0F, 0.0F };
    scale_    = Vector3D{ 1.0F, 1.0F, 1.0F };
    rotation_ = Vector3D{ 0.0F, 0.0F, 0.0F };

    return true;
}

// I—¹
void Transform3D::finalize()
{
}

} // namespace component
END_EGEG
// EOF
