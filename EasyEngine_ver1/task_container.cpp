// 作成者 : 板場
#include "task_container.hpp"

BEGIN_EGEG
// TaskContainer
/*===========================================================================*/
// コンストラクタ
TaskContainer::TaskContainer() :
    index_( 0U )
{
    task_list_.reserve( 128U );
}

// タスクの削除
void TaskContainer::remove( Task* pTask )
{
    // コンテナの走査
    for( auto itr = task_list_.begin(), end = task_list_.end();
        itr != end; ++itr )
    {
        // 対象のタスクをコンテナから削除
        if( (*itr) == pTask )
        {
            task_list_.erase( itr );
            break;
        }
    }
}

// タスクの取り出し
Task* TaskContainer::pick()
{
    unsigned curr_idx = index_++;
    
    // 実行対象のタスクがある
    if( curr_idx < task_list_.size() )
    {
        return task_list_[ curr_idx ];
    }
    // 実行対象のタスクがない
    {
        index_ = 0U;
        return nullptr;
    }
}
END_EGEG
// EOF
