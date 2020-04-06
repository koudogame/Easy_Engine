///
/// @file   job_scheduler.hpp
/// @author ��
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
/// @brief  �W���u�̎��s�����Ǘ��N���X
///
/// @tparam JobType  : �Ǘ�����W���u�^
/// @tparam Executer : �W���u�����s����t�@���N�^
///
template <class JobType, class JobExecuterType = DefaultExecuter>
class JobScheduler : protected JobExecuterType
{
public :
    ///
    /// @brief  �W���u�̓o�^
    ///
    /// @param[in] Register : �o�^����W���u
    /// @param[in] Priority : �D��x( �Ⴂ�قǗD��x������ : ��Ɏ��s����� )
    ///
    void registerJob( JobType* Register, uint32_t Priority = 0U )
    {
        JobContainer<JobType>* container = &container_list_[Priority];
        container->entry( Register );
        Register->setContainer( container );
    }

    ///< �W���u�̓o�^����
    void unregisterJob( JobType* Unregister )
    {
        Unregister->exitFromContainer();
    }

    ///
    /// @brief  �Ǘ����Ă���W���u�̎��s
    ///
    /// @param[in] ...Args : ���s����W���u�֓n��������
    ///
    template <class ...ArgTypes>
    void execute( ArgTypes ...Args )
    {
        for( auto& container : container_list_ )
        { // �R���e�i�𑖍�
            while( JobType* job = container.second.pick() )
            { // �W���u�𑖍�
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
