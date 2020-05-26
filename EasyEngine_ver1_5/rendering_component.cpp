// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "rendering_component.hpp"
#include "level.hpp"


BEGIN_EGEG

/******************************************************************************

	RenderingComponent

******************************************************************************/
 // ������
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


 // �I��
void RenderingComponent::finalize()
{
	affiliation_scene_->exit( this );
}

END_EGEG
// EOF
