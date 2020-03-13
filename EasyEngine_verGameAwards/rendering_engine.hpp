///
/// @file   rendering_engine.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#define INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
#include <memory>
#include <unordered_map>
#include <d3d11.h>
#include "egeg_utility.hpp"
BEGIN_EGEG
class VertexShader;
class GeometryShader;
class PixelShader;

///
/// @class   RenderingEngine
/// @brief   �`��G���W��
/// @details �V���O���g���N���X�ł��B2��ȏ�create�֐��͌Ăяo���Ȃ��ł��������B
///
class RenderingEngine final :
    public std::enable_shared_from_this<RenderingEngine>,
    NonCopyable<RenderingEngine>
{
public :
    ~RenderingEngine();

    static std::shared_ptr<RenderingEngine> create();

    D3D_FEATURE_LEVEL getFeatureLevel() const noexcept { return feature_level_; }
    ID3D11Device* getDevice() const noexcept { device_->AddRef(); return device_; }
    ID3D11DeviceContext* getDeviceContext() const noexcept { device_context_->AddRef(); return device_context_; }

    ///
    /// @brief   �V�F�[�_�\�̐���
    ///
    /// @tparam ShaderType : ��������V�F�[�_�[�^
    ///
    /// @return ���������V�F�[�_�[
    ///
    template <class ShaderType>
    std::unique_ptr<ShaderType> createShader() const;

    ///
    /// @brief  �V�[���̐���
    ///
    /// @tparam SceneType : ��������V�[���^
    ///
    /// @return ���������V�[��
    ///
    template <class SceneType>
    std::unique_ptr<SceneType> createScene() const;

private :
    RenderingEngine() = default;

    D3D_FEATURE_LEVEL    feature_level_;
    ID3D11Device*        device_ = nullptr;
    ID3D11DeviceContext* device_context_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_ENGINE_HEADER_
/// EOF
