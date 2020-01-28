///
/// @file    job_scheduler.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#define INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#include <cstdint>
#include <map>
#include "job.hpp"
#include "job_container.hpp"
BEGIN_EGEG
///
/// @class JobScheduler
///          
/// @brief   ジョブスケジューラー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          登録された関数をexecute関数で一度に呼び出します。
///
class JobScheduler
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static JobScheduler* instance() { static JobScheduler i; return &i; }

    ///
    /// @brief   ジョブの登録
    /// @details 実行優先度は、数の小さいほうが優先です。
    ///
    /// @param[in] Priority : 実行優先度
    /// @param[in] pJob : 登録するジョブのアドレス
    ///
    void registerJob( uint32_t Priority, Job* pJob );

    ///
    /// @brief  ジョブの登録解除
    ///
    /// @param[in] pJob : 登録を解除するジョブのアドレス
    ///
    void unregisterJob( Job* pJob );

    ///
    /// @brief  ジョブの実行
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの経過時間
    ///
    void execute( uint64_t DeltaTimeMS );

private :
    JobScheduler();
    JobScheduler( JobScheduler& ) = delete;
    JobScheduler& operator=( JobScheduler& ) = delete;

    std::map<uint32_t, JobContainer> job_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
/// EOF
