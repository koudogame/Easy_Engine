// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "level.hpp"
#include "engine.hpp"
#include "application_status.hpp"
#include "task_order.hpp"


BEGIN_EGEG

/******************************************************************************

	Level

******************************************************************************/
 // ������
bool Level::initialize( std::istream& DataStream )
{
    if( !initScene() ) return false;
    if( !loadActor(DataStream) ) return false;

    task_.setJob( this, &Level::render );
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kRender );

    return true;
}


 // �I��
void Level::finalize()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_ );

    for( auto& actor : actors_ )
        actor->finalize();
    actors_.clear();
    scene_.finalize();
}


 // �`��
void Level::render( uint64_t )
{
    scene_.clear( EasyEngine::getRenderingManager()->getD3DDeviceContext().Get() );
    scene_.render( EasyEngine::getRenderingManager()->getD3DDeviceContext().Get() );
    swap_chain_->Present( 0, 0 );
}


 // �V�[��������
bool Level::initScene()
{
    using namespace Microsoft::WRL;

    if( !scene_.initialize(EasyEngine::getRenderingManager()->getD3DDevice().Get()) ) 
        return false;

    auto* renderer = EasyEngine::getRenderingManager();
    
    // swap chain
    DXGI_SWAP_CHAIN_DESC sc_desc{};
    sc_desc.BufferCount = 1;
    sc_desc.BufferDesc.Width = kWindowWidth<UINT>;
    sc_desc.BufferDesc.Height = kWindowHeight<UINT>;
    sc_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sc_desc.BufferDesc.RefreshRate.Numerator = 60;
    sc_desc.BufferDesc.RefreshRate.Denominator = 1;
    sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc_desc.OutputWindow = EasyEngine::getWindowHandle();
    sc_desc.SampleDesc.Count = 1;
    sc_desc.SampleDesc.Quality = 0;
    sc_desc.Windowed = true;
    sc_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    ComPtr<IDXGIFactory> factory;
    HRESULT hr = CreateDXGIFactory( IID_PPV_ARGS(&factory) );
    if( FAILED(hr) ) return false;
    hr = factory->CreateSwapChain( renderer->getD3DDevice().Get(), &sc_desc, &swap_chain_ );
    if( FAILED(hr) ) return false;

    // render target view
    ComPtr<ID3D11Texture2D> back_buffer;
    hr = swap_chain_->GetBuffer( 0, _uuidof(ID3D11Texture2D), &back_buffer );
    if( FAILED(hr) ) return false;
    ComPtr<ID3D11RenderTargetView> rtv;
    hr = renderer->getD3DDevice()->CreateRenderTargetView( back_buffer.Get(), nullptr, &rtv );
    if( FAILED(hr) ) return false;

    // viewport
    D3D11_VIEWPORT vp{
        0.0F,
        0.0F,
        kWindowWidth<float>,
        kWindowHeight<float>,
        0.0F,
        1.0F 
    };

    // depth stencil texture
    D3D11_TEXTURE2D_DESC texture_desc{};
    texture_desc.Width              = kWindowWidth<UINT>;
    texture_desc.Height             = kWindowHeight<UINT>;
    texture_desc.MipLevels          = 1;
    texture_desc.ArraySize          = 1;
    texture_desc.Format             = DXGI_FORMAT_D32_FLOAT;
    texture_desc.SampleDesc.Count   = 1;
    texture_desc.SampleDesc.Quality = 0;
    texture_desc.Usage              = D3D11_USAGE_DEFAULT;
    texture_desc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
    ComPtr<ID3D11Texture2D> texture;
    hr = renderer->getD3DDevice()->CreateTexture2D( &texture_desc, nullptr, &texture );
    if( FAILED(hr) ) return false;
    // depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc{};
    dsv_desc.Format = texture_desc.Format;
    dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    ComPtr<ID3D11DepthStencilView> dsv;
    hr = renderer->getD3DDevice()->CreateDepthStencilView( texture.Get(), &dsv_desc, &dsv );
    if( FAILED(hr) ) return false;

    // �V�[���X�e�[�g�ݒ�
    scene_.setState( {rtv}, {vp}, {}, dsv );

    return true;
}


 // �A�N�^�[�ǂݍ���
#undef max
bool Level::loadActor( std::istream& Stream )
{
    std::string type;
    while( Stream >> type )
    {
        if( type == "#" )
        { // �R�����g
            Stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        else
        { // �A�N�^�[�̓ǂݍ���
            auto actor = ActorFactory::create( type );
            if( !actor )
              // �Ή����Ă��Ȃ��A�N�^�[�͖�������
                continue;
            
            actor->setAffiliationLevel( *this );
            if( !actor->initialize(Stream) )
            { // ���s�@��n�������ď������I����
                for( auto& act : actors_ )
                    act->finalize();
                actors_.clear();
                return false;
            }

            actors_.push_back( std::move(actor) );
        }
    }

    return true;
}

END_EGEG
// EOF
