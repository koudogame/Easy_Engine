// �쐬�� : ��
#include "collision_space.hpp"

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
END_EGEG
// EOF
