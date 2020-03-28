// �쐬�� : ��
#include "texture_loader.hpp"
#include "lib/DirectXTex.h"

#ifdef _DEBUG
#pragma comment( lib, "lib/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "lib/Release/DirectXTex.lib" )
#endif


BEGIN_EGEG

// TextureLoader �֐���`
/*===========================================================================*/
// �e�N�X�`���̃��[�h
//
// DirectXTex�𗘗p���ăe�N�X�`�������[�h����
// �߂�l�̓e�N�X�`���̃V�F�[�_�\���\�[�X�r���[
DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>
TextureLoader::load( const std::wstring& FilePath )
{
    using RetTy = DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
    using namespace DirectX;

    // �t�@�C������f�[�^��ǂݍ���
    TexMetadata metadata;
    ScratchImage image;
    HRESULT hr = LoadFromWICFile(FilePath.c_str(), 0, &metadata, image);
    if( FAILED(hr) ) { RetTy(false, nullptr, "�t�@�C���ǂݍ��݂Ɏ��s"); }

    // �V�F�[�_�\���\�[�X�r���[���쐬
    ID3D11ShaderResourceView* srv = nullptr;
    hr = CreateShaderResourceViewEx(
        device_.Get(),
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_SHADER_RESOURCE,
        0,
        0,
        false,
        &srv
    );
    if( FAILED(hr) ) { RetTy(false, nullptr, "�V�F�[�_�\���\�[�X�r���[�̐����Ɏ��s"); }

    RetTy ret( true, srv );
    srv->Release();
    return ret;
}

END_EGEG
// EOF
