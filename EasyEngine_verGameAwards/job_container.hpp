///
/// @file   job_container.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#define INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#include <functional>
#include <vector>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  JobContainer
/// @brief  �W���u�R���e�i
///
/// @tparam JobType : �Ǘ�����W���u�̌^
///
template <class JobType>
class JobContainer
{
public :
    ///< �R���X�g���N�^
    JobContainer( size_t Reserved = 32U )
    {
        job_list_.reserve( Reserved );
    }
    ///< �f�X�g���N�^
    ~JobContainer()
    {
        // �W���u�𑖍�
        index_ = 0U;
        while( JobType* job = pick() )
        {
            job->exitFromContainer();
        }
    }

    ///
    /// @brief   �W���u�̓o�^
    /// @details nullptr�͓o�^���Ȃ��ŉ������B<br>
    ///          �W���u�̉����͕K��exit�֐����g�p���ĉ������B
    ///
    /// @param[in] Entry : �o�^����W���u
    ///
    void entry( JobType* Entry ) 
    {
        // �W���u��o�^
        if( empty_idx_list_.size() )
        { // �W���u���X�g�ɋ󂫂�����ꍇ
            job_list_.at(empty_idx_list_.back()) = Entry;
            empty_idx_list_.pop_back();
        }
        else
        { // �W���u���X�g�ɋ󂫂��Ȃ��ꍇ
            job_list_.push_back( Entry ); 
        }
    }
    ///
    /// @brief  �W���u�̉���
    ///
    /// @param[in] Exit : ��������W���u
    ///
    void exit( JobType* Exit ) 
    {
        auto begin = job_list_.begin();
        auto itr = std::find(begin, job_list_.end(), Exit);
        *itr = nullptr;
        empty_idx_list_.push_back( std::distance(begin, itr) );
    }

    ///
    /// @brief   �Ώۂ̃W���u�����o��
    /// @details �Ăяo�����Ɏw�����J�E���g���Ă����A�Ō��nullptr��ԋp���܂��B
    ///
    /// @return ���݂̎w���ɑΉ������W���u
    ///
    JobType* pick()
    {
        auto curr_idx = index_++;
        if( curr_idx >= job_list_.size() )
        { // �v�f�����ׂăs�b�N����
            index_ = 0U;
            return nullptr;
        }

        JobType* job = job_list_.at( curr_idx );

        // ��̃W���u�̓X�L�b�v
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
