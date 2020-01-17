///
/// @file    task_manager.hpp
/// @author  板場
///          
/// @brief   タスクマネージャー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。
///
#ifndef INCLUDED_EGEG_TASK_MANAGER_HEADER_
#define INCLUDED_EGEG_TASK_MANAGER_HEADER_
#include <cstdint>
#include <map>
#include "task.hpp"
#include "task_container.hpp"
BEGIN_EGEG
class TaskManager
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static TaskManager* instance() { static TaskManager i; return &i; }

    ///
    /// @brief   タスクの登録
    /// @details 実行優先度は、数の小さいほうが優先です。
    ///
    /// @param[in] Priority : 実行優先度
    /// @param[in] pTask : 登録するタスクのアドレス
    ///
    void registerTask( uint32_t Priority, Task* pTask );

    ///
    /// @brief  タスクの登録解除
    ///
    /// @param[in] pTask : 登録を解除するタスクのアドレス
    ///
    void unregisterTask( Task* pTask );
    ///
    /// @brief   タスクの登録解除( 優先度指定 )
    /// @details 優先度を指定することで探索を少しだけ早くします。
    ///

    ///
    /// @brief  タスクの実行
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの経過時間
    ///
    void execute( uint64_t DeltaTimeMS );

private :
    TaskManager();
    TaskManager( TaskManager& ) = delete;
    TaskManager& operator=( TaskManager& ) = delete;

    std::map<uint32_t, TaskContainer> task_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TASK_MANAGER_HEADER_
/// EOF
