// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "transform3d_component.hpp"


BEGIN_EGEG

/******************************************************************************

	Transform3DComponent

******************************************************************************/
 // 初期化
bool Transform3DComponent::initialize()
{
	is_moved_ = true;
	position_ = Vector3D{ 0.0F, 0.0F, 0.0F };
	rotation_ = Vector3D{ 0.0F, 0.0F, 0.0F };
	scale_    = Vector3D{ 1.0F, 1.0F, 1.0F };
	transform_cache_ = DirectX::XMMatrixIdentity();

	return true;
}


 // 終了
void Transform3DComponent::finalize()
{
}


 // ローカル座標変換行列を計算
const Matrix4x4& Transform3DComponent::calcLocalTransformMatrix() const
{
	using namespace DirectX;

	if( !is_moved_ ) return transform_cache_;

	const auto kScaling{ XMMatrixScalingFromVector( getScale() ) };
	const auto kRotation{ XMMatrixRotationRollPitchYawFromVector( getRotation() ) };
	const auto kTranslation { XMMatrixTranslationFromVector( getPosition() ) };

	transform_cache_ = Matrix4x4{ XMMatrixMultiply( kScaling, kRotation ) };
	transform_cache_ = Matrix4x4{ XMMatrixMultiply( transform_cache_, kTranslation ) };

	is_moved_ = false;
	return transform_cache_;
}


 // グローバル変換変換行列を計算
Matrix4x4 Transform3DComponent::calcGlobalTransformMatrix() const
{
	using namespace DirectX;

	Matrix4x4 global = calcLocalTransformMatrix();
	while( auto* parent = getOwner()->getParent() )
	{
		if( auto* parent_transform = parent->getComponent<Transform3DComponent>() )
			global = Matrix4x4{ XMMatrixMultiply(global, parent_transform->calcLocalTransformMatrix()) };
	}

	return global;
}


END_EGEG
// EOF
