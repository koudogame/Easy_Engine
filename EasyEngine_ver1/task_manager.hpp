///
/// @file    task_manager.hpp
/// @author  ��
///          
/// @brief   �^�X�N�}�l�[�W���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B
///
#ifndef INCLUDED_EGEG_TASK_MANAGER_HEADER_
#define INCLUDED_EGEG_TASK_MANAGER_HEADER_
#include <cstdint>
#include <map>
#include "task.hpp"
#include "task_container.hpp"
BEGIN_EGEG
class TaskManager
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static TaskManager* instance() { static TaskManager i; return &i; }

    ///
    /// @brief   �^�X�N�̓o�^
    /// @details ���s�D��x�́A���̏������ق����D��ł��B
    ///
    /// @param[in] Priority : ���s�D��x
    /// @param[in] pTask : �o�^����^�X�N�̃A�h���X
    ///
    void registerTask( uint32_t Priority, Task* pTask );

    ///
    /// @brief  �^�X�N�̓o�^����
    ///
    /// @param[in] pTask : �o�^����������^�X�N�̃A�h���X
    ///
    void unregisterTask( Task* pTask );
    ///
    /// @brief   �^�X�N�̓o�^����( �D��x�w�� )
    /// @details �D��x���w�肷�邱�ƂŒT�������������������܂��B
    ///

    ///
    /// @brief  �^�X�N�̎��s
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̌o�ߎ���
    ///
    void execute( uint64_t DeltaTimeMS );

private :
    TaskManager();
    TaskManager( TaskManager& ) = delete;
    TaskManager& operator=( TaskManager& ) = delete;

    std::map<uint32_t, TaskContainer> task_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TASK_MANAGER_HEADER_
/// EOF
