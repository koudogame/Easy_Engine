// 作成者 : 板場
#include "rendering_engine.hpp"
#ifdef _DEBUG
#include <cassert>
#endif
#include <stdexcept>
#include "utility_function.hpp"
#include "error.hpp"
#include "shader_loader.hpp"

#pragma comment ( lib, "d3d11.lib" )

namespace
{
    D3D_FEATURE_LEVEL kFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1
    };


#ifdef _DEBUG
    constexpr UINT kCreateDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
    constexpr UINT kCreateDeviceFlag = 0;
#endif
} // unnamed namespace

BEGIN_EGEG

// RenderingEngine 関数定義
/*===========================================================================*/
// Dtor
RenderingEngine::~RenderingEngine()
{
}

// レンダリングエンジン生成
std::shared_ptr<RenderingEngine> RenderingEngine::create()
{
#ifdef _DEBUG
    static unsigned created_cnt;
    assert( !created_cnt++ && "RenderingEngineはSingletonクラスです。" );
#endif
    RenderingEngine* created = new RenderingEngine();

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        ::kCreateDeviceFlag,
        ::kFeatureLevels,
        getArraySize(::kFeatureLevels),
        D3D11_SDK_VERSION,
        &created->device_,
        &created->feature_level_,
        &created->immediate_context_
    );

    if( FAILED(hr) )
    {
        // WARPデバイス
        hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_WARP,
            nullptr,
            kCreateDeviceFlag,
            ::kFeatureLevels,
            getArraySize(::kFeatureLevels),
            D3D11_SDK_VERSION,
            &created->device_,
            &created->feature_level_,
            &created->immediate_context_
        );

        if( FAILED(hr) )
        {
            delete created;
            throw std::runtime_error( "レンダリングエンジンの生成に失敗しました。" );
        }
    }

    // シェーダーローダーの作成
    created->shader_loader_ = std::make_shared<ShaderLoader>( created->device_ );
    return std::shared_ptr<RenderingEngine>( created );
}

END_EGEG
// EOF
