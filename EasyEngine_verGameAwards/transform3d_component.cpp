// 作成者 : 板場
#include "transform3d_component.hpp"

BEGIN_EGEG

// Transform3DComponent 関数定義
/*===========================================================================*/
// 初期化
bool Transform3DComponent::initialize()
{
    position_ = Vector3D{ 0.0F, 0.0F, 0.0F };
    scale_    = Vector3D{ 1.0F, 1.0F, 1.0F };
    rotation_ = Vector3D{ 0.0F, 0.0F, 0.0F };

    return true;
}

// 終了
void Transform3DComponent::finalize()
{
}

END_EGEG
// EOF
