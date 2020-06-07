// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "rendering_manager.hpp"
#ifdef _DEBUG
#include <cassert>
#endif
#include "engine.hpp"
#include "application_status.hpp"
#include "task_order.hpp"


/******************************************************************************

	library

******************************************************************************/
#pragma comment( lib, "dxgi.lib"  )
#pragma comment( lib, "d3d11.lib" )


BEGIN_EGEG

/******************************************************************************

	constant & declaration

******************************************************************************/
namespace
{
	void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC* ) noexcept;

    constexpr D3D_FEATURE_LEVEL kFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
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
 // デストラクタ
 //
 // 画面更新のタスクはゲーム中常に存在するだろうという認識で、タスクの登録を解除していない
RenderingManager::~RenderingManager() = default;


 // 生成処理
std::unique_ptr<RenderingManager> RenderingManager::create()
{
#ifdef _DEBUG
    static unsigned created_cnt_;
	assert( !created_cnt_++ && "RenderingManagerを複数生成することはできません。" );
#endif
	auto created = std::unique_ptr<RenderingManager>{ new RenderingManager{} };

	DXGI_SWAP_CHAIN_DESC sc_desc{};
	setSwapChainDesc( &sc_desc );
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
	    nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		kCreateDeviceFlag,
		kFeatureLevels,
		ARRAYSIZE( kFeatureLevels ),
		D3D11_SDK_VERSION,
		&sc_desc,
		&created->dxgi_swap_chain_,
		&created->d3d_device_,
		&created->d3d_feature_level_,
		&created->d3d_immediate_context_
	);
	if( FAILED(hr) ) return nullptr;

	// バックバッファへのビューを取得
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
	hr = created->dxgi_swap_chain_->GetBuffer( 0, __uuidof(ID3D11Texture2D), &backbuffer );
	if( FAILED(hr) ) return nullptr;
	hr = created->d3d_device_->CreateRenderTargetView( backbuffer.Get(), nullptr, &created->main_render_target_ );
	if( FAILED(hr) ) return nullptr;

	created->texture_loader_ = std::make_unique<TextureLoader>();
	created->texture_loader_->setManager( *created.get() );

	created->shader_loader_ = std::make_unique<ShaderLoader>();
	created->shader_loader_->setManager( *created.get() );

	created->obj_loader_ = std::make_unique<WavefrontobjLoader>();
	created->obj_loader_->setManager( *created.get() );

	created->task_.setJob( created.get(), &RenderingManager::present );
	EasyEngine::getTaskManager()->registerJob( &created->task_, TaskOrder::kRenderEnd+1 );

	return created;
}
 

 // 画面更新
void RenderingManager::present( uint64_t )
{
	dxgi_swap_chain_->Present( 0, 0 );
}


/******************************************************************************

	other

******************************************************************************/
namespace
{

 // スワップチェインの設定を出力
void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC* Output ) noexcept
{
    Output->BufferCount = 1;
    Output->BufferDesc.Width = kWindowWidth<UINT>;
    Output->BufferDesc.Height = kWindowHeight<UINT>;
    Output->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    Output->BufferDesc.RefreshRate.Numerator = 60;
    Output->BufferDesc.RefreshRate.Denominator = 1;
    Output->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    Output->OutputWindow = EasyEngine::getWindowHandle();
    Output->SampleDesc.Count = 1;
    Output->SampleDesc.Quality = 0;
    Output->Windowed = true;
    Output->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
}

}

END_EGEG
// EOF
