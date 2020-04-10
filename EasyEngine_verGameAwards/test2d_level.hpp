#pragma once

#include <wrl.h>
#include "level.hpp"
#include "task.hpp"
#include "scene2d.hpp"
#include "test2d_actor.hpp"

class Test2DLevel :
    public EGEG Level
{
public :
    Test2DLevel( EGEG LevelManager* Manager ) :
        Level( Manager )
    {
    }

    // override
    bool initialize() override;
    void finalize() override;

    void update( uint64_t );

private :
    Microsoft::WRL::ComPtr<IDXGISwapChain> sc_;
    D3D11_VIEWPORT viewport_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv_;

    EGEG Task task_;
    EGEG Scene2D scene_;
    Test2DActor actor_;
};

REGISTER_LEVEL( Test2DLevel );
// EOF
