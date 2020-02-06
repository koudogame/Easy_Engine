///
/// @file   fullscan_spatial_division.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_FULLSCAN_SPATIAL_DIVISION_HEADER_
#define INCLUDED_EGEG_FULLSCAN_SPATIAL_DIVISION_HEADER_
#include "collision_section.hpp"
BEGIN_EGEG
///
/// @class  FullScanSpatialDivision
/// @brief  �S�����Փ˔���N���X�B��Ԃ̕����͍s��Ȃ�
///
class FullScanSpatialDivision
{
public :
    void setSections( std::vector<CollisionSection>* pContainer )
    {
        pContainer->push_back( CollisionSection() );
    }
    uint32_t createID( const Shape* )
    {
        return 0U;
    }
};
END_EGEG
#endif /// !INCLUDED_EGEG_FULLSCAN_SPATIAL_DIVISION_HEADER_
/// EOF
