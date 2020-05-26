// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "texture_loader.hpp"
#include "rendering_manager.hpp"
#include "lib/DirectXTex/DirectXTex.h"


/******************************************************************************

	library

******************************************************************************/
#ifdef _DEBUG
#pragma comment( lib, "lib/DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "lib/DirectXTex/Release/DirectXTex.lib" )
#endif


BEGIN_EGEG

/******************************************************************************

	TextureLoader

******************************************************************************/
 // �e�N�X�`���̓ǂݍ���
DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>
TextureLoader::load( const std::string& FilePath )
{
    using namespace DirectX;

	// �t�@�C������wchar_t�^�ɕϊ�
	wchar_t* w_str = new wchar_t[FilePath.size()+1U];
    size_t res;
    auto err = mbstowcs_s( &res, w_str, FilePath.size()+1U, FilePath.c_str(), FilePath.size() );
    if( err || res != FilePath.size()+1U ) 
    {
        delete[] w_str;
        return { Failure{}, "�t�@�C�����̕ϊ��Ɏ��s" };
    }

	// �t�@�C������f�[�^��ǂݍ���
	TexMetadata metadata{};
	ScratchImage image{};
	HRESULT hr = LoadFromWICFile( w_str, 0, &metadata, image );
	delete[] w_str;
	if( FAILED(hr) ) return { Failure{}, "�t�@�C���̓ǂݍ��݂Ɏ��s" };

	// �e�N�X�`���̃r���[���쐬
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv{};
	hr = CreateShaderResourceViewEx(
	    getManager()->getD3DDevice().Get(),
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
	if( FAILED(hr) ) return { Failure{}, "�V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s" };

	return { Success{}, std::move(srv) };
}

END_EGEG
// EOF
