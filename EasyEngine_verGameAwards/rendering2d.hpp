///
/// @file   rendering2d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_

#include "component2d.hpp"

BEGIN_EGEG
namespace component
{

///
/// @class  Rendering2D
/// @brief  描画コンポーネント
///
class Rendering2D :
    public Component2D
{
    static constexpr TypeID<Rendering2D> getID() noexcept { return TypeID<Rendering2D>(); }

    Rendering2D( Actor2D* Owner ) :
        Component2D( Owner )
    {}


    
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize()   override;
/*-----------------------------------------------------------------*/
private :

};

} // namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_
/// EOF
