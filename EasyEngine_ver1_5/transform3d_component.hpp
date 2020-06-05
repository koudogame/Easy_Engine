///
/// @file   transform3d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_

#include "component.hpp"

BEGIN_EGEG

///
/// @class  Transform3DComponent
/// @brief  3D座標変換コンポーネント
///
/// @details 3D座標系で扱われます。
///
class Transform3DComponent :
    public Component
{
public :
    Transform3DComponent( LevelNode* Owner ) :
        Component{ Owner } {}

// override
    bool initialize() override;
    void finalize() override;

private :
    
};

END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM3D_COMPONENT_HEADER_
/// EOF
