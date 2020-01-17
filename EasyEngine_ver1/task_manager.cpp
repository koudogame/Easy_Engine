// 作成者 : 板場
#include "task_manager.hpp"

BEGIN_EGEG
// TaskManager
/*===========================================================================*/
// コンストラクタ
TaskManager::TaskManager()
{
}

// タスクの登録
void TaskManager::registerTask( uint32_t Priority, Task* pTask )
{
    task_list_[Priority].insert(pTask);
    pTask->setContainer( &task_list_[Priority] );
}

// タスクの登録解除
void TaskManager::unregisterTask( Task* pTask )
{
    pTask->getContainer()->remove( pTask );
}

// タスクの実行
void TaskManager::execute( uint64_t Delta )
{
    Task* task = nullptr;   // 実行対象

    // タスクの全走査
    for( auto itr = task_list_.begin(), end = task_list_.end(); itr != end; ++itr )
    {
        // 同一優先度要素の走査
        while( (task = itr->second.pick()) != nullptr )
        {
            (*task)( Delta );
        }
    }
}
END_EGEG
// EOF
