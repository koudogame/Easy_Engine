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
 // デストラクタ
LevelNode::~LevelNode()
{
	leaveFromParent();
}


 // 子ノードの削除
void LevelNode::removeChild( LevelNode* Child )
{
	auto find_itr = std::find_if( childs_.begin(), childs_.end(), 
		[=]( const std::unique_ptr<LevelNode>& Ptr )
	{
		return Ptr.get()==Child;
	});
	if( find_itr != childs_.end() )
	{
		childs_.erase( find_itr );
	}
}


 // 親ノードとの親子関係を切る
void LevelNode::leaveFromParent()
{
	if( parent_ )
	{
		parent_->removeChild( this );
		parent_ = nullptr;
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
