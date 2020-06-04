// ì¬ŽÒ : ”Âê
/******************************************************************************

	include

******************************************************************************/
#include "level_node.hpp"
#include "component.hpp"


BEGIN_EGEG

/******************************************************************************

	LevelNode::ComponentDeleter

******************************************************************************/
 // operator()
void LevelNode::ComponentDeleter::operator()( Component* Ptr ) const
{
	Ptr->finalize();
	delete Ptr;
}

END_EGEG
// EOF
