#pragma once

#include <memory>
#include "actor2d.hpp"
#include "task.hpp"
#include "test2d_vs.hpp"
#include "test2d_ps.hpp"

class Test2DActor :
    public EGEG Actor2D
{
public :
    Test2DActor() :
        Actor2D( 0 )
    {}

    // overrides 
    bool initialize() override;
    void finalize() override;

    void update( uint64_t );

private :
    EGEG Task task_;
    std::unique_ptr<Test2DVertexShader> vs_;
    std::unique_ptr<Test2DPixelShader>  ps_;
};
// EOF
