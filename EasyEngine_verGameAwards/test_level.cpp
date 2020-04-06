#include "test_level.hpp"
#include "application_status.hpp"
#include "shader_loader.hpp"
#include "WavefrontOBJ_loader.hpp"
#include "rendering3d.hpp"
#include "transform3d.hpp"

BEGIN_EGEG

bool TestLevel::initialize()
{
    if( !scene_.initialize( EasyEngine::getRenderingManager()->getDevice().Get()) ) return false;
    if( !actor_.initialize() ) return false;

    camera_position_ = Vector3D{ 0.0F, 0.0F, -5.0F };
    camera_focus_ = Vector3D{ 0.0F, 0.0F, 10.0F };
    camera_.setViewMatrix(
        DirectX::XMMatrixLookAtLH(
            camera_position_,
            camera_focus_,
            {0.0F, 1.0F, 0.0F}
        ) 
    );
    scene_.setCamera( &camera_ );
    
    actor_.addComponent<component::Transform3D>()->setPosition( {0.0F, 0.0F, 0.0F} );
    actor_.getComponent<component::Transform3D>()->setScale( {0.5F, 0.5F, 0.5F} );

    auto loader = EasyEngine::getRenderingManager()->getShaderLoader();
    auto vs = loader->loadVertexShader<TestVS>();
    auto ps = loader->loadPixelShader<TestPS>();

    auto obj_loader = EasyEngine::getRenderingManager()->getModelLoader();
    model_.vertex_shader = std::move(vs);
    model_.pixel_shader = std::move(ps);
    obj_loader->load( "character.obj", &model_.mesh );
    
    auto component = actor_.addComponent<component::Rendering3D>();
    component->setModel( model_ );
   
    actor_.controller = new XInputController( XInputP1::instance() );
    actor_.controller->registerFunction( XInputController::Buttons::kDpadRight, &actor_, &TestActor::moveRight );
    actor_.controller->registerFunction(
        XInputController::Sticks::kLeftStick,
        [&]( float X, float Y )
        {
            auto transform = actor_.getComponent<component::Transform3D>();
            if( transform )
            {
                auto rotation = transform->getRotation();
                float angle = std::atan2(Y, X);
                rotation.z = angle;
                transform->setRotation( rotation );
            }
        }
    );

    return true;
}
void TestLevel::finalize()
{
    delete actor_.controller;
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
    //if( XInputP1::instance()->getState().dpad_right ) after.x += 0.1F;
    actor_.getComponent<component::Transform3D>()->setPosition( after );

    actor_.controller->update();

    DirectX::XMFLOAT4X4 view;
    DirectX::XMStoreFloat4x4(
        &view,
        DirectX::XMMatrixLookAtLH(
            camera_position_,
            camera_focus_,
            {0.0F, 1.0F, 0.0F}
        )
    );
    //camera_.setViewMatrix( view );

    scene_.entry( &actor_ );

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rs;
    D3D11_RASTERIZER_DESC dc {};
    dc.FillMode = D3D11_FILL_SOLID;
    dc.CullMode = D3D11_CULL_BACK;
    EasyEngine::getRenderingManager()->getDevice()->CreateRasterizerState(
        &dc, &rs );

    scene_.render(
        EasyEngine::getRenderingManager()->getImmediateContext().Get(),
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
