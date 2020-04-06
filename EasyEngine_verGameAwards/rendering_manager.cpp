// �쐬�� : ��
#include "rendering_manager.hpp"
#ifdef _DEBUG
#include <cassert>
#endif
#include <stdexcept>
#include "utility_function.hpp"
#include "error.hpp"
#include "texture_loader.hpp"
#include "shader_loader.hpp"
#include "WavefrontOBJ_loader.hpp"

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

// RenderingManager �֐���`
/*===========================================================================*/
// Dtor
RenderingManager::~RenderingManager()
{
}

// �����_�����O�G���W������
std::unique_ptr<RenderingManager> RenderingManager::create()
{
#ifdef _DEBUG
    static unsigned created_cnt;
    assert( !created_cnt++ && "RenderingManager�̓V���O���g���N���X�ł��B" );
#endif
    std::unique_ptr<RenderingManager> created( new RenderingManager() );


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
        // WARP�f�o�C�X
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
            throw std::runtime_error( "�����_�����O�G���W���̐����Ɏ��s���܂����B" );
        }
    }

    // �e�N�X�`�����[�_�[�̍쐬
    created->texture_loader_ = std::make_unique<TextureLoader>();
    created->texture_loader_->setRenderingEngine( created.get() );

    // �V�F�[�_�[���[�_�[�̍쐬
    created->shader_loader_ = std::make_unique<ShaderLoader>();
    created->shader_loader_->setRenderingEngine( created.get() );

    // ���f�����[�_�[�̍쐬
    created->model_loader_ = std::make_unique<WavefrontOBJLoader>();
    created->model_loader_->setRenderingEngine( created.get() );


    return created;
}

END_EGEG
// EOF
