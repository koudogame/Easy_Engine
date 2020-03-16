///
/// @file   scene2d.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_SCENE2D_HEADER_
#define INCLUDED_EGEG_SCENE2D_HEADER_
#include "scene.hpp"
#include "actor2d.hpp"
BEGIN_EGEG
///
/// @class  Scene2D
/// @brief  2DÉVÅ[Éì
///
class Scene2D :
    public Scene
{
public :
    Scene2D( ID3D11DeviceContext* ImmediateContext ) :
        Scene( ImmediateContext )
    {}

protected :
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE2D_HEADER_
/// EOF
