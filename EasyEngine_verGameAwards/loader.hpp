///
/// @file   loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LOADER_HEADER_
#define INCLUDED_EGEG_LOADER_HEADER_
#include <wrl.h>
#include <d3d11.h>
#include "easy_engine.hpp"
#include "noncopyable.hpp"
BEGIN_EGEG
///
/// @class  Loader
/// @brief  ローダー
///
class Loader :
    NonCopyable<Loader>
{
public :
    Loader( const Microsoft::WRL::ComPtr<ID3D11Device>& Device ) :
        device_( Device )
    {
    }
    virtual ~Loader() = default;

protected :
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_LOADER_HEADER_
/// EOF
