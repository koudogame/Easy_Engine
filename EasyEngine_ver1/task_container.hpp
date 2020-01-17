///
/// @file   task_container.hpp
/// @author 板場
///
/// @brief  タスクコンテナ
///
#ifndef INCLUDED_EGEG_TASK_CONTAINER_HEADER_
#define INCLUDED_EGEG_TASK_CONTAINER_HEADER_
#include <vector>
#include "task.hpp"
BEGIN_EGEG
class TaskContainer
{
public :
    TaskContainer();

    ///
    /// @brief  タスクの追加
    ///
    /// @param[in] pTask : 追加するタスク
    ///
    void insert( Task* pTask )
    {
        task_list_.push_back( pTask );
    }

    ///
    /// @brief  タスクの削除
    ///
    /// @param[in] pTask : 削除するタスク
    ///
    void remove( Task* pTask );

    ///
    /// @brief   タスクの取り出し
    /// @details 現在実行対象のタスクを取り出します。<br>
    ///          実行対象のタスクが無くなったらnullptrを返却します。
    ///
    /// @return タスク
    ///
    Task* pick();

private :
    unsigned index_;
    std::vector<Task*> task_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TASK_CONTAINER_HEADER_
/// EOF
