///
/// @file   job_container.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#define INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#include <functional>
#include <vector>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  JobContainer
/// @brief  ジョブコンテナ
///
/// @tparam JobType : 管理するジョブの型
///
template <class JobType>
class JobContainer
{
public :
    ///< コンストラクタ
    JobContainer( size_t Reserved = 32U )
    {
        job_list_.reserve( Reserved );
    }
    ///< デストラクタ
    ~JobContainer()
    {
        // ジョブを走査
        for( auto job : job_list_ )
        { // 自身に登録してあるジョブを解除
            job->exitFromContainer();
        }
    }

    ///
    /// @brief  ジョブの登録
    ///
    /// @param[in] Entry : 登録するジョブ
    ///
    void entry( JobType* Entry ) { job_list_.push_back( Entry ); }
    ///
    /// @brief  ジョブの解除
    ///
    /// @param[in] Exit : 解除するジョブ
    ///
    void exit( JobType* Exit ) { job_list_.erase( std::find(job_list_.cbegin(), job_list_.cend(), Exit) ); }

    ///
    /// @brief  対象のジョブを取り出す
    ///
    /// @return 現在の指数に対応したジョブ
    ///
    JobType* pick()
    {
        auto curr_idx = index_++;
        if( curr_idx >= job_list_.size() )
        { // 要素をすべてピックした
            index_ = 0U;
            return nullptr;
        }

        return job_list_.at( curr_idx );
    }

private :
    unsigned index_ = 0U;
    std::vector<JobType*> job_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_CONTAINER_HEADER_
/// EOF
