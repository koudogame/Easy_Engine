// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "actor2d.hpp"
#include "application_status.hpp"
#include "transform2d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Actor2D

******************************************************************************/
 // ワールド変換行列の計算
DirectX::XMMATRIX Actor2D::calcWorldMatrix() const
{
    using namespace DirectX;

    auto* transform = getComponent<Transform2DComponent>();
    if( !transform ) return XMMatrixIdentity();

    return DirectX::XMMatrixAffineTransformation2D(
        transform->getScale(),
        transform->getPosition() + transform->getPivot(),
        XMConvertToRadians( transform->getRotationDeg() ),
        transform->getPosition()
    );
}

END_EGEG
// EOF
