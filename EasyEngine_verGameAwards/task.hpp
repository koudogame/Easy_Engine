///
/// @file   task.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TASK_HEADER_
#define INCLUDED_EGEG_TASK_HEADER_

#include <cstdint>
#include <functional>
#include "job.hpp"

BEGIN_EGEG

///
/// @class  Task
/// @brief  �^�X�N�}�l�[�W���[�ɓo�^����P��
///
class Task :
    protected Job<void(uint64_t)>
{
public :
    using Job::operator();
    using Job::setContainer;
    using Job::exitFromContainer;

    ///
    /// @brief   �W���u�Ƃ��Ď��s����֐��̃Z�b�g
    /// @details ex.) .setJob( this, &Hoge::update );   <br>
    ///          �Z�b�g����֐��́A                     <br>
    ///            �u�����o�֐��v                       <br>
    ///            �u�߂�lvoid�v                       <br>
    ///            �u����uint64_t�v                     <br>
    ///          �Ƃ����v���𖞂����Ă��������B
    ///
    /// @param[in] Owner    : �֐��̎��s��
    /// @param[in] Function : ���s����֐�( �����o�֐� )
    ///
    template <class OwnerType>
    void setJob( OwnerType* Owner, void(OwnerType::*Function)(uint64_t) )
    {
        Job::setJob( std::bind(Function, Owner, std::placeholders::_1) );
    }

    Job* operator&() { return this; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_HEADER_
/// EOF
