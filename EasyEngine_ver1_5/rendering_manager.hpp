///
/// @file   rendering_manager.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_HEADER_

#include <memory>
#include <wrl.h>
#include <d3d11.h>
#include "non_copyable.hpp"
#include "texture_loader.hpp"
#include "shader_loader.hpp"
#include "wavefrontobj_loader.hpp"

BEGIN_EGEG

///
/// @class RenderingManager
/// @brief �`��}�l�[�W���\
///
class RenderingManager final :
    NonCopyable<RenderingManager>
{
public :
    static std::unique_ptr<RenderingManager> create();
    ~RenderingManager();

    ///
    /// @brief �̗p���ꂽ�@�\���x���̎擾
    ///
    /// @return �̗p���ꂽ�@�\���x��
    ///
    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return d3d_feature_level_; }

    ///
    /// @brief D3D�f�o�C�X�̎擾
    ///
    /// @return D3D�f�o�C�X
    ///
    Microsoft::WRL::ComPtr<ID3D11Device> getD3DDevice() const noexcept { return d3d_device_; }

    ///
    /// @brief D3D�f�o�C�X�R���e�L�X�g�̎擾
    ///
    /// @return D3D�f�o�C�X�R���e�L�X�g
    ///
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getD3DDeviceContext() const noexcept { return d3d_immediate_context_; }

    ///
    /// @brief  �e�N�X�`�����[�_�[�̎擾
    ///
    /// @return �e�N�X�`�����[�_�[
    ///
    TextureLoader* getTextureLoader() const noexcept { return texture_loader_.get(); };

    ///
    /// @brief  �V�F�[�_�[���[�_�[�̎擾
    ///
    /// @return �V�F�[�_�[���[�_�[
    ///
    ShaderLoader* getShaderLoader() const noexcept { return shader_loader_.get(); }

    ///
    /// @brief  WavefrontOBJ�`���t�@�C���p���[�_�[�̎擾
    ///
    /// @return ���f�����[�_�[
    ///
    WavefrontobjLoader* getObjLoader() const noexcept { return obj_loader_.get(); }

private :
    RenderingManager() = default;

    D3D_FEATURE_LEVEL d3d_feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_immediate_context_;
    std::unique_ptr<TextureLoader> texture_loader_;
    std::unique_ptr<ShaderLoader>  shader_loader_;
    std::unique_ptr<WavefrontobjLoader> obj_loader_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
/// EOF
