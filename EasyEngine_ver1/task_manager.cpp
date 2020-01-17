// �쐬�� : ��
#include "task_manager.hpp"

BEGIN_EGEG
// TaskManager
/*===========================================================================*/
// �R���X�g���N�^
TaskManager::TaskManager()
{
}

// �^�X�N�̓o�^
void TaskManager::registerTask( uint32_t Priority, Task* pTask )
{
    task_list_[Priority].insert(pTask);
    pTask->setContainer( &task_list_[Priority] );
}

// �^�X�N�̓o�^����
void TaskManager::unregisterTask( Task* pTask )
{
    pTask->getContainer()->remove( pTask );
}

// �^�X�N�̎��s
void TaskManager::execute( uint64_t Delta )
{
    Task* task = nullptr;   // ���s�Ώ�

    // �^�X�N�̑S����
    for( auto itr = task_list_.begin(), end = task_list_.end(); itr != end; ++itr )
    {
        // ����D��x�v�f�̑���
        while( (task = itr->second.pick()) != nullptr )
        {
            (*task)( Delta );
        }
    }
}
END_EGEG
// EOF
