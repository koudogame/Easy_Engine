// 作成者 : 板場
#include "transform3d.hpp"

BEGIN_EGEG
namespace component {

// Transform3D 関数定義
/*===========================================================================*/
// 初期化
bool Transform3D::initialize()
{
    position_ = Vector3D{ 0.0F, 0.0F, 0.0F };
    scale_    = Vector3D{ 1.0F, 1.0F, 1.0F };
    rotation_ = Vector3D{ 0.0F, 0.0F, 0.0F };

    return true;
}

// 終了
void Transform3D::finalize()
{
}

} // namespace component
END_EGEG
// EOF
