// ì¬ŽÒ : ”Âê
/******************************************************************************

	include

******************************************************************************/
#include "rendering_component.hpp"
#include "level.hpp"


BEGIN_EGEG

/******************************************************************************

	RenderingComponent

******************************************************************************/
 // ‰Šú‰»
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


 // I—¹
void RenderingComponent::finalize()
{
	affiliation_scene_->exit( this );
}

END_EGEG
// EOF
