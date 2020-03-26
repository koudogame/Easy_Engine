#include "test_level.hpp"
#include "application_status.hpp"
#include "shader_loader.hpp"
#include "WavefrontOBJ_loader.hpp"
#include "rendering3d.hpp"
#include "transform3d.hpp"

BEGIN_EGEG

bool TestLevel::initialize()
{
    if( !scene_.initialize() ) return false;
    if( !actor_.initialize() ) return false;

    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4(
        &view,
        DirectX::XMMatrixLookAtLH(
            {0.0F, 0.0F, -1.0F},
            {0.0F, 0.0F, 0.0F},
            {0.0F, 1.0F, 0.0F}
        )
    );

    camera_.setViewMatrix( view );
    camera_position_ = {0.0F, 0.0F, -1.0F};
    scene_.setCamera( &camera_ );
    
    actor_.addComponent<component::Transform3D>()->setPosition( {0.0F, 0.0F, 0.0F} );

    ShaderLoader loader{ EasyEngine::getRenderingEngine()->getDevice() };
    auto vs = loader.loadVertexShader<TestVS>();
    auto ps = loader.loadPixelShader<TestPS>();

    WavefrontOBJLoader obj_loader( EasyEngine::getRenderingEngine()->getDevice() );
    model_.vertex_shader = std::move(vs);
    model_.pixel_shader = std::move(ps);
    model_.mesh = obj_loader.loadMesh( "character.obj" );
    
    auto component = actor_.addComponent<component::Rendering3D>();
    component->setModel( model_ );

    return true;
}
void TestLevel::finalize()
{
    actor_.finalize();
    scene_.finalize();
}

void TestLevel::update( ID3D11RenderTargetView* RTV )
{
    Vector3D after = actor_.getComponent<component::Transform3D>()->getPosition();
    XInputP1::instance()->update();
    if( XInputP1::instance()->getState().dpad_up )    after.z += 0.1F;
    if( XInputP1::instance()->getState().dpad_down )  after.z -= 0.1F;
    if( XInputP1::instance()->getState().dpad_left )  after.x -= 0.1F;
    if( XInputP1::instance()->getState().dpad_right ) after.x += 0.1F;
    actor_.getComponent<component::Transform3D>()->setPosition( after );

    Vector3D scale {
        XInputP1::instance()->getState().right_thumbstick_x + 1.0F,
        XInputP1::instance()->getState().right_thumbstick_y + 1.0F,
        1.0F 
    };
    actor_.getComponent<component::Transform3D>()->setScale( scale );

    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4(
        &view,
        DirectX::XMMatrixLookToLH(
            DirectX::XMLoadFloat3(&camera_position_),
            {0.0F, 0.0F, 1.0},
            {0.0F, -1.0F, 0.0F}
        )
    );
    camera_.setViewMatrix( view );

    scene_.entry( &actor_ );

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rs;
    D3D11_RASTERIZER_DESC dc {};
    dc.FillMode = D3D11_FILL_SOLID;
    dc.CullMode = D3D11_CULL_BACK;
    EasyEngine::getRenderingEngine()->getDevice()->CreateRasterizerState(
        &dc, &rs );

    scene_.render(
        {RTV},
        {{
            0.0F,
            0.0F,
            kHorizontalResolution<float>,
            kVerticalResolution<float>,
            0.0F,
            1.0F
        }},
        {},
        nullptr,
        nullptr,
        0,
        rs.Get()
    );

}

END_EGEG
// EOF
