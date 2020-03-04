///
/// @file   job_scheduler.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#define INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#include <map>
#include "job.hpp"
BEGIN_EGEG
///
/// @class  JobScheduler
/// @brief  ジョブの実行順序管理クラス
///
/// @tparam JobRetValType : 管理するジョブの戻り値型
/// @tparam ...JobArgs    : 管理するジョブの仮引数型パラメータパック
///
template <class JobRetValType, class ...JobArgs>
class JobScheduler
{
public :
    using JobType = Job<JobRetValType, JobArgs...>;

    ///
    /// @brief  ジョブの登録
    ///
    /// @param[in] ContainerID : 登録するコンテナID
    /// @param[in] Register    : 登録するジョブ
    ///
    void registerJob( uint32_t ContainerID, JobType* Register )
    {
        JobContainer<JobType>* container = &container_list_[ContainerID];
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
    void execute( JobArgs ...Args )
    {
        for( auto& container : container_list_ )
        { // コンテナを走査
            while( JobType* job = container.second.pick() )
            { // コンテナ内のジョブを走査&実行
                (*job)( Args... );
            }
        }
    }

private :
    std::map<uint32_t, JobContainer<JobType>> container_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
/// EOF
