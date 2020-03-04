///
/// @file   job_scheduler.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#define INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#include <map>
#include "job.hpp"
BEGIN_EGEG
class DefaultExecuter
{
public :
    template <class JobType, class ...Ts>
    void operator()( JobType* Job, Ts&& ...Args ) const
    {
        (*Job)( std::forward<Ts>(Args)... );
    }
};
///
/// @class  JobScheduler
/// @brief  �W���u�̎��s�����Ǘ��N���X
///
/// @tparam JobType : �Ǘ�����W���u�^
/// @tparam Executer : �W���u�R���e�i���󂯎��A�W���u�����s����t�@���N�^
///
template <class JobType, class JobExecuterType = DefaultExecuter>
class JobScheduler : public JobExecuterType
{
public :
    ///
    /// @brief  �W���u�̓o�^
    ///
    /// @param[in] Priority : �D��x( �Ⴂ�قǗD��x������ : ��Ɏ��s����� )
    /// @param[in] Register : �o�^����W���u
    ///
    void registerJob( uint32_t Priority, JobType* Register )
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
    template <class ...Ts>
    void execute( Ts&& ...Args )
    {
        for( auto& container : container_list_ )
        { // �R���e�i�𑖍�
            while( JobType* job = container.second.pick() )
            { // �W���u�𑖍�
                JobExecuterType::operator()( job, std::forward<Ts>(Args)... );
            }
        }
    }

private :
    std::map<uint32_t, JobContainer<JobType>> container_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
/// EOF
