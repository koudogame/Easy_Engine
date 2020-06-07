///
/// @file   task.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_TASK_HEADER_
#define INCLUDED_EGEG_TASK_HEADER_

#include <cstdint>
#include <functional>
#include "job.hpp"
#include "job_scheduler.hpp"

BEGIN_EGEG

using TaskManager = JobScheduler<Job<void(uint64_t)>>;

///
/// @class Task
/// @brief �^�X�N�}�l�[�W���[�ɓo�^����W���u�P��
///
class Task :
    protected Job<void(uint64_t)>
{
public :
    ///
    /// @brief   �W���u�̃Z�b�g
    ///
    /// @param[in] Owner    : �֐��̎��s��
    /// @param[in] Function : �W���u�Ƃ��ăZ�b�g����֐�
    ///
    /// @details �Z�b�g����֐��́u�����o�֐��v�u�߂�lvoid�v�u����uint64_t�v�𖞂����Ă��������B <br>
    ///           �g�p�� )                                                                 <br>     
    ///             Task task;                                                             <br>
    ///             task.setJob( this, &Hoge::update );
    ///
    template <class OwnerType>
    void setJob( OwnerType* Owner, void(OwnerType::*Function)(uint64_t) )
    {
        Job::setJob( std::bind( Function, Owner, std::placeholders::_1) );
    }

    Job* operator&() noexcept { return this; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_HEADER_
/// EOF
