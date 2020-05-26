// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "rendering_manager.hpp"
#ifdef _DEBUG
#include <cassert>
#endif


/******************************************************************************

	library

******************************************************************************/
#pragma comment( lib, "dxgi.lib"  )
#pragma comment( lib, "d3d11.lib" )


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    constexpr D3D_FEATURE_LEVEL kFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
	};

#ifdef _DEBUG
	constexpr UINT kCreateDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
	constexpr UINT kCreateDeviceFlag = 0U;
#endif
}


/******************************************************************************

	RenderingManager

******************************************************************************/
 // 生成処理
std::unique_ptr<RenderingManager> RenderingManager::create()
{
#ifdef _DEBUG
    static unsigned created_cnt_;
	assert( !created_cnt_++ && "RenderingManagerを複数生成することはできません。" );
#endif
	auto created = std::unique_ptr<RenderingManager>{ new RenderingManager{} };

	HRESULT hr = D3D11CreateDevice(
	    nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		kCreateDeviceFlag,
		kFeatureLevels,
		ARRAYSIZE( kFeatureLevels ),
		D3D11_SDK_VERSION,
		&created->d3d_device_,
		&created->d3d_feature_level_,
		&created->d3d_immediate_context_
	);
	if( FAILED(hr) ) return nullptr;

	created->texture_loader_ = std::make_unique<TextureLoader>();
	created->texture_loader_->setManager( *created.get() );

	created->shader_loader_ = std::make_unique<ShaderLoader>();
	created->shader_loader_->setManager( *created.get() );

	created->obj_loader_ = std::make_unique<WavefrontobjLoader>();
	created->obj_loader_->setManager( *created.get() );

	return created;
}


 // デストラクタ
RenderingManager::~RenderingManager() = default;

END_EGEG
// EOF
