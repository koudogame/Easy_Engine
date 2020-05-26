// 作成者 : 板場
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
 // テクスチャの読み込み
DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>
TextureLoader::load( const std::string& FilePath )
{
    using namespace DirectX;

	// ファイル名をwchar_t型に変換
	wchar_t* w_str = new wchar_t[FilePath.size()+1U];
    size_t res;
    auto err = mbstowcs_s( &res, w_str, FilePath.size()+1U, FilePath.c_str(), FilePath.size() );
    if( err || res != FilePath.size()+1U ) 
    {
        delete[] w_str;
        return { Failure{}, "ファイル名の変換に失敗" };
    }

	// ファイルからデータを読み込む
	TexMetadata metadata{};
	ScratchImage image{};
	HRESULT hr = LoadFromWICFile( w_str, 0, &metadata, image );
	delete[] w_str;
	if( FAILED(hr) ) return { Failure{}, "ファイルの読み込みに失敗" };

	// テクスチャのビューを作成
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
	if( FAILED(hr) ) return { Failure{}, "シェーダーリソースビューの作成に失敗" };

	return { Success{}, std::move(srv) };
}

END_EGEG
// EOF
