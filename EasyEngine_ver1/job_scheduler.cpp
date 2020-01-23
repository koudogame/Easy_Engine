// 作成者 : 板場
#include "job_scheduler.hpp"

BEGIN_EGEG
// TaskManager
/*===========================================================================*/
// コンストラクタ
JobScheduler::JobScheduler()
{
}

// ジョブの登録
void JobScheduler::registerJob( uint32_t Priority, Job* pJob )
{
    job_list_[Priority].insert(pJob);
    pJob->setContainer( &job_list_[Priority] );
}

// ジョブの登録解除
void JobScheduler::unregisterJob( Job* pJob )
{
    pJob->getContainer()->remove( pJob );
}

// ジョブの実行
void JobScheduler::execute( uint64_t Delta )
{
    Job* job = nullptr;   // 実行対象

    // ジョブの全走査
    for( auto itr = job_list_.begin(), end = job_list_.end(); itr != end; ++itr )
    {
        // 同一優先度要素の走査
        while( (job = itr->second.pick()) != nullptr )
        {
            (*job)( Delta );
        }
    }
}
END_EGEG
// EOF
