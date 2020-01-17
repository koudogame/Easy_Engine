///
/// @file   task_container.hpp
/// @author ��
///
/// @brief  �^�X�N�R���e�i
///
#ifndef INCLUDED_EGEG_TASK_CONTAINER_HEADER_
#define INCLUDED_EGEG_TASK_CONTAINER_HEADER_
#include <vector>
#include "task.hpp"
BEGIN_EGEG
class TaskContainer
{
public :
    TaskContainer();

    ///
    /// @brief  �^�X�N�̒ǉ�
    ///
    /// @param[in] pTask : �ǉ�����^�X�N
    ///
    void insert( Task* pTask )
    {
        task_list_.push_back( pTask );
    }

    ///
    /// @brief  �^�X�N�̍폜
    ///
    /// @param[in] pTask : �폜����^�X�N
    ///
    void remove( Task* pTask );

    ///
    /// @brief   �^�X�N�̎��o��
    /// @details ���ݎ��s�Ώۂ̃^�X�N�����o���܂��B<br>
    ///          ���s�Ώۂ̃^�X�N�������Ȃ�����nullptr��ԋp���܂��B
    ///
    /// @return �^�X�N
    ///
    Task* pick();

private :
    unsigned index_;
    std::vector<Task*> task_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TASK_CONTAINER_HEADER_
/// EOF
