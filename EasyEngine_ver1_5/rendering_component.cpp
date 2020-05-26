// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "rendering_component.hpp"
#include "level.hpp"


BEGIN_EGEG

/******************************************************************************

	RenderingComponent

******************************************************************************/
 // 初期化
bool RenderingComponent::initialize()
{
	auto* level = getOwner()->getAffiliationLevel();
	if( level )
	{
	    auto* scene = level->getScene();
		scene->entry( this );
		affiliation_scene_ = scene;
	}

	return true;
}


 // 終了
void RenderingComponent::finalize()
{
	affiliation_scene_->exit( this );
}

END_EGEG
// EOF
