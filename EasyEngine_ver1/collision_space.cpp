// �쐬�� : ��
#include "collision_space.hpp"
#include "shape.hpp"
#include "job_scheduler.hpp"

BEGIN_EGEG
// CollisionSpace : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
CollisionSpace::CollisionSpace()
{
    SpatialDivision spatial_division;
    spatial_division.setSections( &sections_ );
    job_.setFunction( this, &CollisionSpace::collision );
    JobScheduler::instance()->registerJob( 0U, &job_ );
}
// �f�X�g���N�^
CollisionSpace::~CollisionSpace()
{
    JobScheduler::instance()->unregisterJob( &job_ );
}

// �Փ˔���
void CollisionSpace::collision( uint64_t )
{
    std::vector<CollisionSection*> to_judge_sections;    // ���胊�X�g
    to_judge_sections.reserve( sections_.size() );

    
    to_judge_sections.push_back( &(*sections_.begin()) );
    CollisionSection* curr_section = to_judge_sections.back();
    while( curr_section != nullptr )
    {
        // ���胊�X�g�ƌ��݂̃Z�N�V�����̔�����s��
        for( auto& section : to_judge_sections )
        {
            if( section == curr_section )
                judgeSameSection( section );
            else
                judgeSectionAndSection( section, curr_section );
        }

        // ���ɔ�����s���Z�N�V�����ւƈڍs
        curr_section = nextJudgeSection( curr_section );

        // ���胊�X�g�ɃZ�N�V������ǉ�
        if( curr_section != nullptr )
        {
            to_judge_sections.push_back( curr_section );
        }
    }
}

// ��Ԃւ̓o�^
void CollisionSpace::entry( CollisionComponent* pComponent )
{
    SpatialDivision spatial_division;
    uint32_t section = spatial_division.createID( pComponent->getShape() );

    sections_[section].entry( pComponent );
}
// ��Ԃ���폜
void CollisionSpace::exit( CollisionComponent* pComponent )
{
    // �����Z�N�V��������폜
    pComponent->getBelongSection()->exit( pComponent );
}


// �Z�N�V�����ƃZ�N�V�����̔��菈��
//
// in Sec1 : �Z�N�V����1
// in Sec2 : �Z�N�V����2
void CollisionSpace::judgeSectionAndSection( CollisionSection* Sec1, CollisionSection* Sec2 )
{
    while( auto sec1_com = Sec1->pickComponent() )
    {
        while( auto sec2_com = Sec2->pickComponent() )
        {
            // �Փ˔���
            if( (sec1_com != sec2_com) &&
                (sec1_com->getShape()->isCollided(sec2_com->getShape())) ) 
            {
                sec1_com->notifyCollision( sec2_com );
                sec2_com->notifyCollision( sec1_com );
            }
        }
    }
}
// ����Z�N�V�������m�̔��菈��
// �����g�ݍ��킹�̏Փ˔�����s��Ȃ��悤����
//
// in Sec : �Z�N�V����
void CollisionSpace::judgeSameSection( CollisionSection* Sec )
{
    // �Z�N�V�������̃R���|�[�l���g�����X�g��
    std::vector<CollisionComponent*> objects;
    objects.reserve( 32U );
    while( auto component = Sec->pickComponent() )
    {
        objects.push_back( component );
    }

    // �����g�ݍ��킹�������悤����
    for( int i = objects.size() - 1U; i >= 0; --i )
    {
        for( int j = i - 1U; j >= 0; --j )
        {
            // �Փ˔���
            if( objects[i]->getShape()->isCollided( objects[j]->getShape()) )
            {
                objects[i]->notifyCollision( objects[j] );
                objects[j]->notifyCollision( objects[i] );
            }
        }
    }
}

// ���݂̃Z�N�V��������A���ɏՓ˂����o����Z�N�V�������擾
//
// in CurrSection : ���݂̃Z�N�V����
//
// return ���ɏՓ˂����o����Z�N�V����
CollisionSection* CollisionSpace::nextJudgeSection( CollisionSection* CurrSection )
{
    CollisionSection* next = CurrSection->pickChild();
    while( next == nullptr )
    {
        // �q�����Ȃ��ꍇ�e�����ֈ�߂�
        CurrSection = CurrSection->getParent();
        if( CurrSection == nullptr ) break;

        next = CurrSection->pickChild();
    }

    return next;
}
END_EGEG
// EOF
