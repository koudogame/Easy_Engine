///
/// @file   fullscan_spatial_division.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_FULLSCAN_SPATIAL_DIVISION_HEADER_
#define INCLUDED_EGEG_FULLSCAN_SPATIAL_DIVISION_HEADER_
#include "collision_section.hpp"
BEGIN_EGEG
///
/// @class  FullScanSpatialDivision
/// @brief  全走査衝突判定クラス。空間の分割は行わない
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
