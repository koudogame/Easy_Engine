///
/// @file   job_scheduler.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#define INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#include <map>
#include "job.hpp"
BEGIN_EGEG
///
/// @class  JobScheduler
/// @brief  �W���u�̎��s�����Ǘ��N���X
///
/// @tparam JobRetValType : �Ǘ�����W���u�̖߂�l�^
/// @tparam ...JobArgs    : �Ǘ�����W���u�̉������^�p�����[�^�p�b�N
///
template <class JobRetValType, class ...JobArgs>
class JobScheduler
{
public :
    using JobType = Job<JobRetValType, JobArgs...>;

    ///
    /// @brief  �W���u�̓o�^
    ///
    /// @param[in] ContainerID : �o�^����R���e�iID
    /// @param[in] Register    : �o�^����W���u
    ///
    void registerJob( uint32_t ContainerID, JobType* Register )
    {
        JobContainer<JobType>* container = &container_list_[ContainerID];
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
    void execute( JobArgs ...Args )
    {
        for( auto& container : container_list_ )
        { // �R���e�i�𑖍�
            while( JobType* job = container.second.pick() )
            { // �R���e�i���̃W���u�𑖍�&���s
                (*job)( Args... );
            }
        }
    }

private :
    std::map<uint32_t, JobContainer<JobType>> container_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
/// EOF
