#include "test_level.hpp"
#include "application_status.hpp"
#include "shader_loader.hpp"
#include "WavefrontOBJ_loader.hpp"
#include "rendering3d_component.hpp"

BEGIN_EGEG

bool TestLevel::initialize()
{
    if( !scene_.initialize() ) return false;
    if( !actor_.initialize() ) return false;

    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4(
        &view,
        DirectX::XMMatrixLookAtLH(
            {0.0F, 0.0F, -0.1F},
            {0.0F, 0.0F, 0.0F},
            {0.0F, 1.0F, 0.0F}
        )
    );

    camera_.setViewMatrix( view );
    camera_position_ = {0.0F, 0.0F, -1.0F};
    scene_.setCamera( &camera_ );
    
    actor_.setPosition( {0.0F, -1.5F, 0.0F} );

    ShaderLoader loader{ EasyEngine::getRenderingEngine()->getDevice() };
    auto vs = loader.loadVertexShader<TestVS>();
    auto ps = loader.loadPixelShader<TestPS>();

    WavefrontOBJLoader obj_loader( EasyEngine::getRenderingEngine()->getDevice() );
    model_.vertex_shader = std::move(vs);
    model_.pixel_shader = std::move(ps);
    model_.mesh = obj_loader.loadMesh( "character.obj" );
    
    auto component = actor_.addComponent<Rendering3DComponent>();
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
    Vector3D after = actor_.getPosition();

    input_.update();
    if( input_.getState().dpad_up )    after.y += 0.1F;
    if( input_.getState().dpad_down )  after.y -= 0.1F;
    if( input_.getState().dpad_left )  after.x -= 0.1F;
    if( input_.getState().dpad_right ) after.x += 0.1F;
    actor_.setPosition( after );

    float angle = std::atan2( input_.getState().left_thumbstick_y, input_.getState().left_thumbstick_x );
    camera_position_.x = std::cos(angle);
    camera_position_.z = std::sin(angle);


    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4(
        &view,
        DirectX::XMMatrixLookToLH(
            DirectX::XMLoadFloat3(&camera_position_),
            {0.0F, 0.0F, 1.0F},
            {0.0F, 1.0F, 0.0F}
        )
    );
    camera_.setViewMatrix( view );

    scene_.entry( &actor_ );

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
        nullptr
    );
}

END_EGEG

