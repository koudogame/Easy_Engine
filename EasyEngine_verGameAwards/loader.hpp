///
/// @file   loader.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_LOADER_HEADER_
#define INCLUDED_EGEG_LOADER_HEADER_
#include <d3d11.h>
#include "rendering_engine_child.hpp"
#include "egeg_utility.hpp"
BEGIN_EGEG
///
/// @class  Loader
/// @brief  ÉçÅ[É_Å[
///
class Loader :
    public RenderingEngineChild,
    NonCopyable<Loader>
{
public :
    Loader( const std::shared_ptr<RenderingEngine>& Engine ) :
        RenderingEngineChild( Engine ),
        device_( Engine->getDevice() )
    {
    }
    virtual ~Loader() { device_->Release(); }

protected :
    ID3D11Device* device_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_LOADER_HEADER_
/// EOF
