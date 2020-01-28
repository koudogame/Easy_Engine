///
/// @file   job_container.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#define INCLUDED_EGEG_JOB_CONTAINER_HEADER_
#include <vector>
#include "job.hpp"
BEGIN_EGEG
///
/// @class  JobContainer
///
/// @brief  �W���u�R���e�i
///
class JobContainer
{
public :
    JobContainer();

    ///
    /// @brief  �W���u�̒ǉ�
    ///
    /// @param[in] pJob: �ǉ�����W���u
    ///
    void insert( Job* pJob )
    {
        job_list_.push_back( pJob );
    }

    ///
    /// @brief  �W���u�̍폜
    ///
    /// @param[in] pJob : �폜����W���u
    ///
    void remove( Job* pJob );

    ///
    /// @brief   �W���u�̎��o��
    /// @details ���ݎ��s�Ώۂ̃W���u�����o���܂��B<br>
    ///          ���s�Ώۂ̃W���u�������Ȃ�����nullptr��ԋp���܂��B
    ///
    /// @return �W���u
    ///
    Job* pick();

private :
    unsigned index_;
    std::vector<Job*> job_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_CONTAINER_HEADER_
/// EOF
