#pragma once

#include "vertex_shader.hpp"

class Test2DVertexShader :
    public EGEG VertexShader
{
public :
    static constexpr D3D11_INPUT_ELEMENT_DESC kInputElementDescs[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            1,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };
    static constexpr const char* kVSFileName = "test2d_vs.cso";

    Test2DVertexShader( ID3D11VertexShader* VS, ID3D11InputLayout* IL ) :
        VertexShader( VS, IL )
    {}

    EGEG DetailedReturnValue<EGEG BindedVertexData> bindVertices( const EGEG Vertex& Vertices ) const override 
    {
        USING_NS_EGEG;
        using RetTy = DetailedReturnValue<BindedVertexData>;
        
        BindedVertexData binded;
        ID3D11Buffer* to_use;
        
        to_use = Vertices.get<Tag_VertexPosition>().Get();
        if( to_use == nullptr )
            return RetTy( false, BindedVertexData{}, "Insufficient vertex data" );
        binded.buffers.push_back( to_use );
        binded.strides.push_back( sizeof(VertexPositionType) );
        binded.offsets.push_back( 0 );

        to_use = Vertices.get<Tag_VertexUV>().Get();
        if( to_use == nullptr )
            return RetTy( false, BindedVertexData{}, "Insufficient vertex data" );
        binded.buffers.push_back( to_use );
        binded.strides.push_back( sizeof(VertexUVType) );
        binded.offsets.push_back( 0 );

        return RetTy( true, std::move(binded) );
    }

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetShader( shader_.Get(), nullptr, 0 );
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
