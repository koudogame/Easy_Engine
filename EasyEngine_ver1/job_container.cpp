// �쐬�� : ��
#include "job_container.hpp"

BEGIN_EGEG
// TaskContainer
/*===========================================================================*/
// �R���X�g���N�^
JobContainer::JobContainer() :
    index_( 0U )
{
    job_list_.reserve( 128U );
}

// �W���u�̍폜
void JobContainer::remove( Job* pTask )
{
    // �R���e�i�̑���
    for( auto itr = job_list_.begin(), end = job_list_.end();
        itr != end; ++itr )
    {
        // �Ώۂ̃^�X�N���R���e�i����폜
        if( (*itr) == pTask )
        {
            job_list_.erase( itr );
            break;
        }
    }
}

// �W���u�̎��o��
Job* JobContainer::pick()
{
    unsigned curr_idx = index_++;
    
    // ���s�Ώۂ̃W���u������
    if( curr_idx < job_list_.size() )
    {
        return job_list_[ curr_idx ];
    }
    // ���s�Ώۂ̃W���u���Ȃ�
    {
        index_ = 0U;
        return nullptr;
    }
}
END_EGEG
// EOF
