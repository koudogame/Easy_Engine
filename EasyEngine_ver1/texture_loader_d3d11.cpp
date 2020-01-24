// �쐬�� : ��
#include "texture_loader_d3d11.hpp"
#include "DirectXTex/DirectXTex.h"
#include "texture_d3d11.hpp"

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif // !_DEBUG

BEGIN_EGEG
// TextureLoaderD3D11
/*===========================================================================*/
// �R���X�g���N�^
TextureLoaderD3D11::TextureLoaderD3D11( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}

// �f�X�g���N�^
TextureLoaderD3D11::~TextureLoaderD3D11()
{
    p_device_->Release();
}

// �e�N�X�`�����\�[�X�̓ǂݍ���
bool TextureLoaderD3D11::load( const std::wstring& Path, ITexture** ppTexture )
{
    using namespace DirectX;

    // �t�@�C������f�[�^��ǂݍ���
    TexMetadata mdata;
    ScratchImage image;
    if( FAILED(LoadFromWICFile(Path.c_str(), 0, &mdata, image)) )
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

    *ppTexture = new TextureD3D11( view );
    view->Release();

    return true;
}
END_EGEG
// EOF
