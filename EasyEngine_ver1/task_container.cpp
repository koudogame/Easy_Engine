// �쐬�� : ��
#include "task_container.hpp"

BEGIN_EGEG
// TaskContainer
/*===========================================================================*/
// �R���X�g���N�^
TaskContainer::TaskContainer() :
    index_( 0U )
{
    task_list_.reserve( 128U );
}

// �^�X�N�̍폜
void TaskContainer::remove( Task* pTask )
{
    // �R���e�i�̑���
    for( auto itr = task_list_.begin(), end = task_list_.end();
        itr != end; ++itr )
    {
        // �Ώۂ̃^�X�N���R���e�i����폜
        if( (*itr) == pTask )
        {
            task_list_.erase( itr );
            break;
        }
    }
}

// �^�X�N�̎��o��
Task* TaskContainer::pick()
{
    unsigned curr_idx = index_++;
    
    // ���s�Ώۂ̃^�X�N������
    if( curr_idx < task_list_.size() )
    {
        return task_list_[ curr_idx ];
    }
    // ���s�Ώۂ̃^�X�N���Ȃ�
    {
        index_ = 0U;
        return nullptr;
    }
}
END_EGEG
// EOF
