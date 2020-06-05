// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "level_node.hpp"
#include "component.hpp"


BEGIN_EGEG

/******************************************************************************

	LevelNode

******************************************************************************/
 // 子ノードの削除
void LevelNode::removeChild( LevelNode* Child )
{
	auto find_itr = std::find( childs_.begin(), childs_.end(), Child );
	if( find_itr != childs_.end() )
	{
		childs_.erase( find_itr );
	}
}


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
