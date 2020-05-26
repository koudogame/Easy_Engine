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

    const float kRotationRad = XMConvertToRadians( transform->getRotationDeg() );

    return DirectX::XMMatrixAffineTransformation2D(
        transform->getScale(),
        transform->getPosition() + transform->getPivot(),
        kRotationRad,
        transform->getPosition()
    );
}

END_EGEG
// EOF
