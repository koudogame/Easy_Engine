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
        for( auto job : job_list_ )
        { // ���g�ɓo�^���Ă���W���u������
            job->exitFromContainer();
        }
    }

    ///
    /// @brief  �W���u�̓o�^
    ///
    /// @param[in] Entry : �o�^����W���u
    ///
    void entry( JobType* Entry ) { job_list_.push_back( Entry ); }
    ///
    /// @brief  �W���u�̉���
    ///
    /// @param[in] Exit : ��������W���u
    ///
    void exit( JobType* Exit ) { job_list_.erase( std::find(job_list_.cbegin(), job_list_.cend(), Exit) ); }

    ///
    /// @brief  �Ώۂ̃W���u�����o��
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

        return job_list_.at( curr_idx );
    }

private :
    unsigned index_ = 0U;
    std::vector<JobType*> job_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_CONTAINER_HEADER_
/// EOF
