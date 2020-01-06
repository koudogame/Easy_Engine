// �쐬�� : ��
#include "renderer_d3d11.hpp"
#include "DirectXTex/DirectXTex.h"
#include "renderer_factory.hpp"

#pragma comment( lib, "d3d11.lib" )

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif

// �����_���[�t�@�N�g����RendererD3D11��o�^
ADD_RENDERER( EG_EG RendererID::kDirect3D11, &RendererD3D11::create )


// unnamed namespace
/*===========================================================================*/
namespace
{
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC*, HWND, UINT, UINT );
    void setViewportDesc( D3D11_VIEWPORT*, float, float );
    template<typename Interface> void safeRelease( Interface*& );

    bool loadBinary( const char*, char*, long* );

#ifdef _DEBUG
    constexpr UINT kD3D11CreateFlags = 0;
#else
    constexpr UINT kD3D11CreateFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

    constexpr D3D_FEATURE_LEVEL kFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
} // unnamed namespace

BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// ����
IRenderer* RendererD3D11::create()
{
    RendererD3D11* p =  new(std::nothrow) RendererD3D11();
    return p;
}
//
//// �e�N�X�`�����\�[�X�̃��[�h
//// ���ꃊ�\�[�X�̓R�s�[����B
//bool RendererD3D11::loadResource( const wchar_t FilePath[], Texture* pOut )
//{
//    using namespace DirectX;
//
//    auto find = textures_.find( FilePath );
//
//    // ���ɓǂݍ��܂�Ă���ꍇ
//    if( find != textures_.end() )
//    {
//        find->second->AddRef();
//        pOut->setResource( find->second );
//    }
//    // �V�K�Ăэ��݂̏ꍇ
//    else
//    {
//        // �t�@�C������f�[�^��ǂݍ���
//        TexMetadata mdata;
//        ScratchImage image;
//        if( FAILED(LoadFromWICFile(FilePath, 0, &mdata, image)) )
//            return false;
//
//        // �r���[���쐬
//        ID3D11ShaderResourceView* view;
//        if( FAILED(CreateShaderResourceViewEx(
//            p_device_,
//            image.GetImages(),
//            image.GetImageCount(),
//            mdata,
//            D3D11_USAGE_DEFAULT,
//            D3D11_BIND_SHADER_RESOURCE,
//            0,
//            0,
//            false,
//            &view)) )
//            return false;
//
//        textures_.insert( std::make_pair(FilePath, view) );
//    }
//
//    return true;
//}
//// �e�N�X�`�����\�[�X�̃A�����[�h
//void RendererD3D11::unloadResource( Texture* pOut )
//{
//    static_cast<ID3D11ShaderResourceView*>( pOut->getResource() )->Release();
//    pOut->setResource( nullptr );
//}
//
//// �V�F�[�_�[�̃��[�h
//// ����V�F�[�_�[�̓R�s�[����B
//bool RendererD3D11::loadVertexShader( const char FilePath[], IShader* pOut )
//{ 
//    if( pOut->getID() != ShaderID::kVertexShader ) 
//        return false;
//
//    char* blob;
//    long  length;
//    ::loadBinary( FilePath, blob, &length );
//
//    ID3D11VertexShader* shader;
//    if( FAILED(p_device_->CreateVertexShader(blob, length, nullptr, &shader)) )
//    {
//        delete blob;
//        return false;
//    }
//
//    return true;
//}
//bool RendererD3D11::loadPixelShader( const char FilePath[], IShader* pOut )
//{
//
//
//    return true;
//}
//// �V�F�[�_�\�̃A�����[�h
//void RendererD3D11::unloadShader( IShader* pShader )
//{
//
//
//}


// ����������
bool RendererD3D11::initialize()
{
    HWND this_window = FindWindow( "Game_Abyabyabyabyabya", nullptr );

    // �E�B���h�E�̈�̎擾
    RECT region;
    if( GetClientRect( this_window, &region ) == false )
        return false;
    const long kRegionWidth = region.right;         // �E�B���h�E�̈敝
    const long kRegionHeight = region.bottom;       // �E�B���h�E�̈捂��

    // D3D�f�o�C�X��DXGI�X���b�v�`�F�C���̍쐬
    DXGI_SWAP_CHAIN_DESC sc_desc = {};
    ::setSwapChainDesc( &sc_desc, this_window, (UINT)kRegionWidth, (UINT)kRegionHeight );
    if( FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        ::kD3D11CreateFlags,
        ::kFeatureLevels,
        sizeof(::kFeatureLevels) / sizeof(D3D_FEATURE_LEVEL),
        D3D11_SDK_VERSION,
        &sc_desc,
        &p_swap_chain_,
        &p_device_,
        &feature_level_,
        &p_immediate_context_)) )
        return false;

    // �`��^�[�Q�b�g���p�C�v���C���ɐݒ�
    ID3D11Texture2D* buffer;
    if( FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer)) )
        return false;
    if( FAILED(p_device_->CreateRenderTargetView(buffer, nullptr, &p_render_target_view_)) )
    {
        buffer->Release();
        return false;
    }
    p_immediate_context_->OMSetRenderTargets( 1, &p_render_target_view_, nullptr );

    // �r���[�|�[�g���p�C�v���C���ɐݒ�
    D3D11_VIEWPORT vp = {};
    ::setViewportDesc( &vp, (float)kRegionWidth, (float)kRegionHeight );
    p_immediate_context_->RSSetViewports( 1, &vp );

    return true;
}
// �I������
void RendererD3D11::finalize()
{
    // �t���X�N���[�����[�h������
    if( p_swap_chain_ )
        p_swap_chain_->SetFullscreenState( false, nullptr );

    // �p�C�v���C���̃X�e�[�g�ݒ���N���A
    if( p_immediate_context_ )
        p_immediate_context_->ClearState();

    // �e��C���^�[�t�F�C�X�����
    ::safeRelease( p_render_target_view_ );
    ::safeRelease( p_swap_chain_ );
    ::safeRelease( p_immediate_context_ );
    ::safeRelease( p_device_ );
}

// �`��J�n
void RendererD3D11::beginRender(float* Color )
{
    p_immediate_context_->ClearRenderTargetView( p_render_target_view_, Color );
}
// ���f���̕`��
void RendererD3D11::render(const Mesh& Object)
{

}
// �`��I��
void RendererD3D11::endRender()
{
    p_swap_chain_->Present(0, 0);
}
END_EG_EG

// unnamed namespace
/*===========================================================================*/
namespace
{
    // �X���b�v�`�F�C���̒�`��ݒ�
    //
    // in pOut   : �o�͗p�\���̂̃A�h���X
    // in hWnd   : �`���E�B���h�E�n���h��
    // in Width  : �o�b�N�o�b�t�@��
    // in Height : �o�b�N�o�b�t�@����
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC* pOut, HWND hWnd, UINT Width, UINT Height )
    {
        pOut->BufferCount = 1;
        pOut->BufferDesc.Width = Width;
        pOut->BufferDesc.Height = Height;
        pOut->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        pOut->BufferDesc.RefreshRate.Numerator = 60;
        pOut->BufferDesc.RefreshRate.Denominator = 1;
        pOut->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        pOut->OutputWindow = hWnd;
        pOut->SampleDesc.Count = 1;
        pOut->SampleDesc.Quality = 0;
        pOut->Windowed = true;
        pOut->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    }
    
    // �r���[�|�[�g�̒�`��ݒ�
    //
    // in pOut   : �o�͗p�\���̂̃A�h���X
    // in Width  : �r���[�|�[�g��
    // in Height : �r���[�|�[�g����
    void setViewportDesc( D3D11_VIEWPORT* pOut, float Width, float Height )
    {
        pOut->Width = Width;
        pOut->Height = Height;
        pOut->MinDepth = 0.0F;
        pOut->MaxDepth = 1.0F;
    }

    // D3D�C���^�[�t�F�C�X�̈��S�ȉ��
    //
    // <in> D3D : �������C���^�[�t�F�C�X�̌^
    //
    // in pInterface
    template <typename Interface>
    void safeRelease( Interface*& Interface )
    {
        if( Interface )
        {
            Interface->Release();
            Interface = nullptr;
        }
    }
} // unnamed namespace
// EOF
