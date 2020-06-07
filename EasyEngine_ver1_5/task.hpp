///
/// @file   task.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_TASK_HEADER_
#define INCLUDED_EGEG_TASK_HEADER_

#include <cstdint>
#include <functional>
#include "job.hpp"
#include "job_scheduler.hpp"

BEGIN_EGEG

using TaskManager = JobScheduler<Job<void(uint64_t)>>;

///
/// @class Task
/// @brief タスクマネージャーに登録するジョブ単位
///
class Task :
    protected Job<void(uint64_t)>
{
public :
    ///
    /// @brief   ジョブのセット
    ///
    /// @param[in] Owner    : 関数の実行者
    /// @param[in] Function : ジョブとしてセットする関数
    ///
    /// @details セットする関数は「メンバ関数」「戻り値void」「引数uint64_t」を満たしてください。 <br>
    ///           使用例 )                                                                 <br>     
    ///             Task task;                                                             <br>
    ///             task.setJob( this, &Hoge::update );
    ///
    template <class OwnerType>
    void setJob( OwnerType* Owner, void(OwnerType::*Function)(uint64_t) )
    {
        Job::setJob( std::bind( Function, Owner, std::placeholders::_1) );
    }

    Job* operator&() noexcept { return this; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_HEADER_
/// EOF
