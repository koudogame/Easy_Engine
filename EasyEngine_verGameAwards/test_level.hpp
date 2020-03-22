#pragma once

#include <d3d11.h>
#include "easy_engine.hpp"
#include "level.hpp"
#include "xinput.hpp"
#include "actor3d.hpp"
#include "model.hpp"
#include "scene3d.hpp"
#include "camera.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"

BEGIN_EGEG
class TestActor :
    public Actor3D
{
public :
    TestActor() :
        Actor3D( UID<TestActor>() )
    {}

    bool initialize() override { return true; }
    void finalize() override {}
};

class TestCamera :
    public Camera
{
public :
    void setViewMatrix( const DirectX::XMFLOAT4X4& Source )
    {
        view_ = Source;
    }
    const DirectX::XMFLOAT4X4& getViewMatrix() const override
    {
        return view_;
    }

private :
    DirectX::XMFLOAT4X4 view_{};
};

class TestVS :
    public VertexShader
{
public :
    static constexpr D3D11_INPUT_ELEMENT_DESC kInputElementDescs[] =
    {
        {
            kVertexPositionSemantic,
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
    };
    static constexpr const char* kVSFileName = "test_vs.cso";

    TestVS( ID3D11VertexShader* VS, ID3D11InputLayout* IL ) :
        VertexShader( VS, IL )
    {}

    VertexBinder getVertexBinder() const override
    {
        return VertexBinder( "POSITION" );
    }

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetShader( shader_.Get(), nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetShaderResources( 0, 0, nullptr );
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetConstantBuffers( 0, 0, nullptr );
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->VSSetSamplers( 0, 0, nullptr );
    }
};
class TestGS :
    public GeometryShader
{
public :
    TestGS( ID3D11GeometryShader* GS ) :
        GeometryShader( GS )
    {}

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetShader( nullptr, nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetShaderResources( 0, 0, nullptr );
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetConstantBuffers( 0, 0, nullptr );
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->GSSetSamplers( 0, 0, nullptr );
    }
};
class TestPS :
    public PixelShader
{
public :
    static constexpr const char* kPSFileName = "test_ps.cso";

    TestPS( ID3D11PixelShader* PS ) :
        PixelShader( PS )
    {}

    void setShaderOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetShader( shader_.Get(), nullptr, 0 );
    }
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetShaderResources( 0, 0, nullptr );
    }
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetConstantBuffers( 0, 0, nullptr );
    }
    void setSamplersOnPipeline( ID3D11DeviceContext* DC ) override
    {
        DC->PSSetSamplers( 0, 0, nullptr );
    }
};



class TestLevel :
    public Level
{
public :
    TestLevel() :
        Level( nullptr ),
        scene_( EasyEngine::getRenderingEngine()->getImmediateContext() )
    {
    }

    bool initialize() override;
    void finalize() override;

    void update( ID3D11RenderTargetView* );

private :
    TestActor actor_;
    Model<TestVS, TestGS, TestPS> model_;
    TestCamera camera_;
    Scene3D scene_;
    XInputP1 input_;
    DirectX::XMFLOAT3 camera_position_;
};

END_EGEG
