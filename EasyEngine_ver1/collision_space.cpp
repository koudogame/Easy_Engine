// �쐬�� : ��
#include "collision_space.hpp"
#include "shape.hpp"

BEGIN_EGEG
// CollisionSpace : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
CollisionSpace::CollisionSpace()
{
    SpatialDivision spatial_division;
    spatial_division.setSections( &sections_ );
}

// �Փ˔���
void CollisionSpace::collision()
{
    std::vector<CollisionSection*> to_judge_sections;    // ���胊�X�g
    to_judge_sections.reserve( sections_.size() );

    
    to_judge_sections.push_back( &(*sections_.begin()) );
    CollisionSection* curr_section = to_judge_sections.back();
    while( curr_section )
    {
        // �Փ˔��胊�X�g�ƌ��݂̃Z�N�V�����̔�����s��
        for( auto& section : to_judge_sections )
        {
            judgeSectionAndSection( section, curr_section );
        }

        // �q�����X�g�ɒǉ�
        CollisionSection* child = curr_section->pickChild();
        while( child == nullptr && curr_section )
        {
            curr_section = curr_section->getParent();
            if( curr_section == nullptr ) break;

            child = curr_section->pickChild();
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
void CollisionSpace::judgeSectionAndSection( CollisionSection* Sec1, CollisionSection* Sec2 )
{
    while( auto sec1_com = Sec1->pickComponent() )
    {
        while( auto sec2_com = Sec2->pickComponent() )
        {
            // �Փ�
            if( sec1_com->getShape()->isCollided(sec2_com->getShape()) ) 
            {
                sec1_com->notifyCollision( sec2_com );
                sec2_com->notifyCollision( sec1_com );
            }
        }
    }
}
END_EGEG
// EOF
