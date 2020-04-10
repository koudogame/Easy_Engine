#pragma once

#include "pixel_shader.hpp"

class Test2DPixelShader :
    public EGEG PixelShader
{
public :
    static constexpr const char* kPSFileName = "test2d_ps.cso";

    Test2DPixelShader( ID3D11PixelShader* PS ) :
        PixelShader( PS )
    {}

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetShader( shader_.Get(), nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
    }

    void setMaterial( const EGEG Material& ) override 
    {
    }

};

// EOF
