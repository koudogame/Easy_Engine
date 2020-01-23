// �쐬�� : ��
#include "job_scheduler.hpp"

BEGIN_EGEG
// TaskManager
/*===========================================================================*/
// �R���X�g���N�^
JobScheduler::JobScheduler()
{
}

// �W���u�̓o�^
void JobScheduler::registerJob( uint32_t Priority, Job* pJob )
{
    job_list_[Priority].insert(pJob);
    pJob->setContainer( &job_list_[Priority] );
}

// �W���u�̓o�^����
void JobScheduler::unregisterJob( Job* pJob )
{
    pJob->getContainer()->remove( pJob );
}

// �W���u�̎��s
void JobScheduler::execute( uint64_t Delta )
{
    Job* job = nullptr;   // ���s�Ώ�

    // �W���u�̑S����
    for( auto itr = job_list_.begin(), end = job_list_.end(); itr != end; ++itr )
    {
        // ����D��x�v�f�̑���
        while( (job = itr->second.pick()) != nullptr )
        {
            (*job)( Delta );
        }
    }
}
END_EGEG
// EOF
