///
/// @file   job_container.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#define INCLUDED_EGEG_JOB_CONTAINER_HEADER_

#include "non_copyable.hpp"

BEGIN_EGEG

///
/// @class  JobContainer
/// @brief  ジョブコンテナ
///
/// @tparam JobType : 管理するジョブの型
///
template <class JobType>
class JobContainer : NonCopyable<JobContainer<JobType>>
{
public :
    ///< コンストラクタ
    JobContainer( size_t Reserved = 128U )
    {
        job_list_.reserve( Reserved );
    }
    ///< デストラクタ
    ~JobContainer()
    {
        // ジョブを走査
        index_ = 0U;
        while( JobType* job = pick() )
        { // ジョブの登録を解除
            // Attention : ここで、既に破棄されたコンテナに対して
            //             Jobが登録解除関数を呼び出してしまうことを避ける。
            job->exitFromContainer();
        }
    }

    ///
    /// @brief   ジョブの登録
    /// @details nullptrは登録しないで下さい。<br>
    ///           ジョブの解除は必ずexit関数を使用して下さい。
    ///
    /// @param[in] Entry : 登録するジョブ
    ///
    void entry( JobType* Entry ) 
    {
        // ジョブを登録
        if( empty_idx_list_.size() )
        { // ジョブリストに空きがある場合
            job_list_.at(empty_idx_list_.back()) = Entry;
            empty_idx_list_.pop_back();
        }
        else
        { // ジョブリストに空きがない場合
            job_list_.push_back( Entry ); 
        }
    }
    ///
    /// @brief  ジョブの解除
    ///
    /// @param[in] Exit : 解除するジョブ
    ///
    void exit( JobType* Exit ) 
    {
        auto begin = job_list_.begin();
        auto itr = std::find(begin, job_list_.end(), Exit);
        *itr = nullptr;
        empty_idx_list_.push_back( std::distance(begin, itr) );
    }

    ///
    /// @brief   対象のジョブを取り出す
    /// @details 呼び出し毎に指数をカウントしていき、最後はnullptrを返却します。
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

        JobType* job = job_list_.at( curr_idx );

        // 空のジョブはスキップ
        if( job == nullptr ) return pick();
        return job;
    }

private :
    unsigned index_ = 0U;
    std::vector<JobType*> job_list_;
    std::vector<size_t> empty_idx_list_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_JOB_CONTAINER_HEADER_
/// EOF
