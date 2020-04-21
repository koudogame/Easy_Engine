///
/// @file   component_id.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_COMPONENT_ID_HEADER_
#define INCLUDED_EGEG_COMPONENT_ID_HEADER_

#include <cstdint>
#include "egeg.hpp"

BEGIN_EGEG

enum ComponentID : uint32_t
{
    kTransform2D = 1U,
    kRendering2D,
    kTransform3D,
    kRendering3D,
    kBody3D,
};

END_EGEG

#endif /// !INCLUDED_EGEG_COMPONENT_ID_HEADER_
/// EOF
