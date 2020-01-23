// 作成者 : 板場
#include "job_container.hpp"

BEGIN_EGEG
// TaskContainer
/*===========================================================================*/
// コンストラクタ
JobContainer::JobContainer() :
    index_( 0U )
{
    job_list_.reserve( 128U );
}

// ジョブの削除
void JobContainer::remove( Job* pTask )
{
    // コンテナの走査
    for( auto itr = job_list_.begin(), end = job_list_.end();
        itr != end; ++itr )
    {
        // 対象のタスクをコンテナから削除
        if( (*itr) == pTask )
        {
            job_list_.erase( itr );
            break;
        }
    }
}

// ジョブの取り出し
Job* JobContainer::pick()
{
    unsigned curr_idx = index_++;
    
    // 実行対象のジョブがある
    if( curr_idx < job_list_.size() )
    {
        return job_list_[ curr_idx ];
    }
    // 実行対象のジョブがない
    {
        index_ = 0U;
        return nullptr;
    }
}
END_EGEG
// EOF
