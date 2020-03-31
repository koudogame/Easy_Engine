///
/// @file   rendering_engine.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#define INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#include <memory>
#include <unordered_map>
#include <wrl.h>
#include <d3d11.h>
#include "noncopyable.hpp"
#include "detailed_returnvalue.hpp"
BEGIN_EGEG
class ShaderLoader;
class WavefrontOBJLoader;

///
/// @class   RenderingEngine
/// @brief   �`��G���W��
/// @details �V���O���g���N���X�ł��B
///
class RenderingEngine final :
    public std::enable_shared_from_this<RenderingEngine>,
    NonCopyable<RenderingEngine>
{
public :
    ~RenderingEngine();

    static std::shared_ptr<RenderingEngine> create();

/* �擾�֐� */

    ///< �g�p���Ă���Direct3D�̋@�\���x���̎擾
    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return feature_level_; }
    ///< �g�p���Ă���f�o�C�X�̎擾
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const noexcept { return device_; }
    ///< �f�o�C�X�R���e�L�X�g�̎擾
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getImmediateContext() const noexcept { return immediate_context_; }

    ///< �V�F�[�_�\���[�_�[�̎擾
    ShaderLoader* getShaderLoader() const noexcept { return shader_loader_.get(); }
    ///< ���f�����[�_�[�̎擾
    WavefrontOBJLoader* getModelLoader() const noexcept { return model_loader_.get(); }

/* �����֐� */

    ///
    /// @brief   �o�b�t�@�I�u�W�F�N�g�̐��� with �����f�[�^
    /// @details �o�b�t�@�T�C�Y�͓����Ōv�Z���Ă��܂��B
    ///
    /// @param[in] BufferDesc : ��������o�b�t�@�̒�`
    /// @param[in] Source     : �o�b�t�@�Ɋi�[����f�[�^
    ///
    /// @return ���������o�b�t�@
    ///
    template <class DataType>
    DetailedReturnValue<bool> createBuffer( D3D11_BUFFER_DESC* BufferDesc, const std::vector<DataType>& Source, ID3D11Buffer** Output );

private :
    RenderingEngine() = default;

    D3D_FEATURE_LEVEL feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_ = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context_ = nullptr;

    std::unique_ptr<ShaderLoader> shader_loader_;
    std::unique_ptr<WavefrontOBJLoader> model_loader_;
};

// �o�b�t�@�I�u�W�F�N�g�̐���
template <class DataType>
DetailedReturnValue<bool> RenderingEngine::createBuffer( D3D11_BUFFER_DESC* Desc, const std::vector<DataType>& Source, ID3D11Buffer** Output )
{
    using RetTy = DetailedReturnValue<bool>;

    Desc->ByteWidth = sizeof(DataType) * Source.size();
    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem = Source.data();

    HRESULT hr = device_->CreateBuffer(
        Desc, &srd, Output );
    if( FAILED(hr) ) return RetTy( false, "�o�b�t�@�I�u�W�F�N�g�̐����Ɏ��s" );

    return RetTy( true );
}

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
/// EOF
