///
/// @file    job_scheduler.hpp
/// @author  ��
///
#ifndef INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#define INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
#include <cstdint>
#include <map>
#include "job.hpp"
#include "job_container.hpp"
BEGIN_EGEG
///
/// @class JobScheduler
///          
/// @brief   �W���u�X�P�W���[���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B<br>
///          �o�^���ꂽ�֐���execute�֐��ň�x�ɌĂяo���܂��B
///
class JobScheduler
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static JobScheduler* instance() { static JobScheduler i; return &i; }

    ///
    /// @brief   �W���u�̓o�^
    /// @details ���s�D��x�́A���̏������ق����D��ł��B
    ///
    /// @param[in] Priority : ���s�D��x
    /// @param[in] pJob : �o�^����W���u�̃A�h���X
    ///
    void registerJob( uint32_t Priority, Job* pJob );

    ///
    /// @brief  �W���u�̓o�^����
    ///
    /// @param[in] pJob : �o�^����������W���u�̃A�h���X
    ///
    void unregisterJob( Job* pJob );

    ///
    /// @brief  �W���u�̎��s
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̌o�ߎ���
    ///
    void execute( uint64_t DeltaTimeMS );

private :
    JobScheduler();
    JobScheduler( JobScheduler& ) = delete;
    JobScheduler& operator=( JobScheduler& ) = delete;

    std::map<uint32_t, JobContainer> job_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_SCHEDULER_HEADER_
/// EOF
