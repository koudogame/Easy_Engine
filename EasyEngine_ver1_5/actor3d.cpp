/// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "actor3d.hpp"
#include "transform3d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Actor3D

******************************************************************************/
 // ワールド変換行列の計算
DirectX::XMMATRIX Actor3D::calcWorldMatrix() const
{
    using namespace DirectX;

    auto* transform = getComponent<Transform3DComponent>();
    if( !transform ) return XMMatrixIdentity();

    const Vector4D kRotationRad {
        XMConvertToRadians(transform->getRotationDeg().x),
        XMConvertToRadians(transform->getRotationDeg().y),
        XMConvertToRadians(transform->getRotationDeg().z),
        1.0F };
    const Matrix4x4 kTranslation{ XMMatrixTranslationFromVector(transform->getPosition()) };
    const Matrix4x4 kScaling{ XMMatrixScalingFromVector(transform->getScale()) };
    const Matrix4x4 kRotation{ XMMatrixRotationRollPitchYawFromVector(kRotationRad) };
    
    XMMATRIX matrix = XMMatrixMultiply( kScaling, kRotation );
    matrix = XMMatrixMultiply( matrix, kTranslation );
    return matrix;
}

END_EGEG
// EOF
