///
/// @file   job_scheduler.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#define INCLUDED_EGEG_JOB_SCHEDULER_HEADER_

#include <type_traits>
#include <map>
#include "job.hpp"

BEGIN_EGEG

class DefaultExecuter
{
public :
    template <class JobType, class ...ArgTypes>
    void operator()( JobType* Job, ArgTypes ...Args ) const
    {
        (*Job)( Args... );
    }
};

///
/// @class  JobScheduler
/// @brief  ジョブの実行順序管理クラス
///
/// @tparam JobType  : 管理するジョブ型
/// @tparam Executer : ジョブを実行するファンクタ
///
template <class JobType, class JobExecuterType = DefaultExecuter>
class JobScheduler : protected JobExecuterType
{
public :
    ///
    /// @brief  ジョブの登録
    ///
    /// @param[in] Register : 登録するジョブ
    /// @param[in] Priority : 優先度( 低いほど優先度が高い : 先に実行される )
    ///
    void registerJob( JobType* Register, uint32_t Priority = 0U )
    {
        JobContainer<JobType>* container = &container_list_[Priority];
        container->entry( Register );
        Register->setContainer( container );
    }

    ///< ジョブの登録解除
    void unregisterJob( JobType* Unregister )
    {
        Unregister->exitFromContainer();
    }

    ///
    /// @brief  管理しているジョブの実行
    ///
    /// @param[in] ...Args : 実行するジョブへ渡す実引数
    ///
    template <class ...ArgTypes>
    void execute( ArgTypes ...Args )
    {
        for( auto& container : container_list_ )
        { // コンテナを走査
            while( JobType* job = container.second.pick() )
            { // ジョブを走査
                JobExecuterType::operator()( job, Args... );
            }
        }
    }

private :
    std::map<uint32_t, JobContainer<JobType>> container_list_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
/// EOF
