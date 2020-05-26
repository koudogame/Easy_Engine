// ì¬ŽÒ : ”Âê
/******************************************************************************

	include

******************************************************************************/
#include "actor.hpp"
#include "component.hpp"


BEGIN_EGEG

/******************************************************************************

	Actor::ComponentDeleter

******************************************************************************/
 // operator()
void Actor::ComponentDeleter::operator()( Component* Ptr ) const
{
    Ptr->finalize();
    delete Ptr;
}

END_EGEG
// EOF
