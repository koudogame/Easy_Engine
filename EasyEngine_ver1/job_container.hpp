///
/// @file   job_container.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#define INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#include <vector>
#include "job.hpp"
BEGIN_EGEG
///
/// @class  JobContainer
///
/// @brief  ジョブコンテナ
///
class JobContainer
{
public :
    JobContainer();

    ///
    /// @brief  ジョブの追加
    ///
    /// @param[in] pJob: 追加するジョブ
    ///
    void insert( Job* pJob )
    {
        job_list_.push_back( pJob );
    }

    ///
    /// @brief  ジョブの削除
    ///
    /// @param[in] pJob : 削除するジョブ
    ///
    void remove( Job* pJob );

    ///
    /// @brief   ジョブの取り出し
    /// @details 現在実行対象のジョブを取り出します。<br>
    ///          実行対象のジョブが無くなったらnullptrを返却します。
    ///
    /// @return ジョブ
    ///
    Job* pick();

private :
    unsigned index_;
    std::vector<Job*> job_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_CONTAINER_HEADER_
/// EOF
