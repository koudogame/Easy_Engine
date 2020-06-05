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
    is_moved_     = false;
    pivot_		  = Vector2D{ 0.0F, 0.0F };
    position_	  = Vector2D{ 0.0F, 0.0F };
    rotation_deg_ = 0.0F;
    scale_        = Vector2D{ 1.0F, 1.0F };

    return true;
}


 // ローカル変換行列を計算
Matrix4x4 Transform2DComponent::calcLocalTransformMatrix() const
{
    using namespace DirectX;

    if( !is_moved_ ) return transform_cache_;

    const auto kToPivot{ XMMatrixTranslationFromVector( getPivot() ) };
    const auto kScaling{ XMMatrixScalingFromVector( getScale() ) };
    const auto kRotation{ XMMatrixRotationZ( XMConvertToRadians(getRotation()) ) };
    const auto kTranslation{ XMMatrixTranslationFromVector( getPosition() ) };

    transform_cache_ = Matrix4x4{ XMMatrixMultiply( kToPivot, kScaling ) };
    transform_cache_ = Matrix4x4{ XMMatrixMultiply( transform_cache_, kScaling ) };
    transform_cache_ = Matrix4x4{ XMMatrixMultiply( transform_cache_, kRotation ) };
    transform_cache_ = Matrix4x4{ XMMatrixMultiply( transform_cache_, kTranslation ) };

    is_moved_ = false;
    return transform_cache_;
}


 // ワールド変換行列を計算
Matrix4x4 Transform2DComponent::calcGlobalTransformMatrix() const
{
    using namespace DirectX;

    Matrix4x4 world = calcLocalTransformMatrix();
    while( auto* parent = getOwner()->getParent() )
    {
        if( auto* parent_transform = parent->getComponent<Transform2DComponent>() )
            world = Matrix4x4{ XMMatrixMultiply(world, parent_transform->calcLocalTransformMatrix() ) };
    }

    return world;
}

END_EGEG
// EOF
