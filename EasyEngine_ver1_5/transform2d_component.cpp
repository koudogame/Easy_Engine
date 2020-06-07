// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "transform2d_component.hpp"
#include <corecrt_math_defines.h>


BEGIN_EGEG

/******************************************************************************

    Transform2DComponent

******************************************************************************/
 // 初期化
bool Transform2DComponent::initialize()
{
    is_moved_     = true;
    pivot_		  = Vector2D{ 0.0F, 0.0F };
    position_	  = Vector2D{ 0.0F, 0.0F };
    rotation_     = 0.0F;
    scale_        = Vector2D{ 1.0F, 1.0F };
    transform_cache_ = DirectX::XMMatrixIdentity();

    return true;
}


 // 終了
void Transform2DComponent::finalize()
{
}


 // ローカル座標変換行列を計算
const Matrix4x4& Transform2DComponent::calcLocalTransformMatrix() const
{
    using namespace DirectX;

    if( !is_moved_ ) return transform_cache_;

    const auto kToPivot{ XMMatrixTranslationFromVector( getPivot() ) };
    const auto kScaling{ XMMatrixScalingFromVector( getScale() ) };
    const auto kRotation{ XMMatrixRotationZ( XMConvertToRadians(getRotation()) ) };
    const auto kTranslation{ XMMatrixTranslationFromVector( getPosition() ) };

    transform_cache_ = Matrix4x4{ XMMatrixMultiply( kToPivot, kScaling ) };
    transform_cache_ = Matrix4x4{ XMMatrixMultiply( transform_cache_, kRotation ) };
    transform_cache_ = Matrix4x4{ XMMatrixMultiply( transform_cache_, kTranslation ) };

    is_moved_ = false;
    return transform_cache_;
}


 // グローバル座標変換行列を計算
Matrix4x4 Transform2DComponent::calcGlobalTransformMatrix() const
{
    using namespace DirectX;

    Matrix4x4 global = calcLocalTransformMatrix();
    while( auto* parent = getOwner()->getParent() )
    {
        if( auto* parent_transform = parent->getComponent<Transform2DComponent>() )
            global = Matrix4x4{ XMMatrixMultiply(global, parent_transform->calcLocalTransformMatrix() ) };
    }

    return global;
}

END_EGEG
// EOF
