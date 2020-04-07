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
#include "egeg_math.hpp"
#include "xinput_controller.hpp"
#include "transform3d.hpp"

BEGIN_EGEG
class TestActor :
    public Actor3D
{
public :
    TestActor() :
        Actor3D( TypeID<TestActor>() )
    {}

    bool initialize() override { return true; }
    void finalize() override {}

    void moveRight( InputDevice::FlagType Input )
    {
        if( InputDevice::isInput( Input ) )
        {
            auto transform = getComponent<component::Transform3D>();
            if( transform )
            {
                auto position = transform->getPosition();
                position.x += 1.0F;
                transform->setPosition( position );
            }
        }
    }

    XInputController* controller;
};

class TestCamera :
    public Camera
{
public :
    void setViewMatrix( const Matrix4x4& Source )
    {
        view_ = Source;
    }
    DirectX::FXMMATRIX getViewMatrix() const override
    {
        return view_;
    }

private :
    Matrix4x4 view_{};
};

class TestVS :
    public VertexShader
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
    };
    static constexpr const char* kVSFileName = "test_vs.cso";

    TestVS( ID3D11VertexShader* VS, ID3D11InputLayout* IL ) :
        VertexShader( VS, IL )
    {}

    DetailedReturnValue<BindedVertexData> bindVertices( const Vertex& Vertices ) const override
    {
        using RetTy = DetailedReturnValue<BindedVertexData>;

        BindedVertexData binded;

        ID3D11Buffer* ver_buf;
        ver_buf = Vertices.get<Tag_VertexPosition>().Get();
        if( ver_buf == nullptr )
        { // 失敗
            return RetTy(false, std::move(binded), "必要なデータがありません" );
        }
        binded.buffers.push_back( ver_buf );
        binded.strides.push_back( sizeof(VertexPositionType) );
        binded.offsets.push_back( 0 );

        return RetTy( true, std::move(binded) );
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

    void setMaterial( const Material& ) override {}
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

    void setMaterial( const Material& ) override {}
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

    void setMaterial( const Material& ) override {}
};



class TestLevel :
    public Level
{
public :
    TestLevel() :
        Level( nullptr )
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
    Vector3D camera_position_;
    Vector3D camera_focus_;
};

END_EGEG
