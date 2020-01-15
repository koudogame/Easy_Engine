// �쐬�� : ��
#include "texture_loader_windows.hpp"
#include "DirectXTex/DirectXTex.h"
#include "texture_windows.hpp"

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif // !_DEBUG

BEGIN_EGEG
// TextureLoaderWindows : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
TextureLoaderWindows::TextureLoaderWindows( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}

// �f�X�g���N�^
TextureLoaderWindows::~TextureLoaderWindows()
{
    p_device_->Release();
}

// �e�N�X�`�����\�[�X�̓ǂݍ���
bool TextureLoaderWindows::load( const wchar_t* Path, ITexture** ppTexture )
{
    using namespace DirectX;

    // �t�@�C������f�[�^��ǂݍ���
    TexMetadata mdata;
    ScratchImage image;
    if( FAILED(LoadFromWICFile(Path, 0, &mdata, image)) )
        return false;

    // �V�F�[�_�[���\�[�X�r���[���쐬
    ID3D11ShaderResourceView* view;
    if( FAILED(CreateShaderResourceViewEx(
        p_device_,
        image.GetImages(),
        image.GetImageCount(),
        mdata,
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_SHADER_RESOURCE,
        0,
        0,
        false,
        &view)) )
        return false;

    *ppTexture = new TextureWindows( view );
    view->Release();

    return true;
}
END_EGEG
// EOF
