///
/// @file   platform_windows.hpp
/// @author ��
///
/// @brief  �v���b�g�t�H�[���uWindows�v
///
#ifndef INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
#define INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
#include <Windows.h>
#include <d3d11.h>
#include "platform.hpp"
BEGIN_EGEG
class PlatformWindows :
    public IPlatform
{
public :
    ///
    /// @brief   PlatformWindows�̐�������
    /// @details PlatformFactory�ɓo�^����֐��ł��B
    ///
    /// @return  new PlatformWindows
    ///
    static IPlatform* create();

// IPlatform
/*-----------------------------------------------------------------*/
    void MainLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const wchar_t* ) override;
    IRenderer* getRenderer() const override { return renderer_; }
    IShaderLoader* getShaderLoader() const override { return shader_loader_; }
    ITextureLoader* getTextureLoader() const override { return texture_loader_; }

private :
    ~PlatformWindows();
    bool initialize();

    HWND h_window_;                             /// �E�B���h�E�n���h��
    D3D_FEATURE_LEVEL feature_level_;           /// �̗p���ꂽDirectX�@�\���x��
    IRenderer* renderer_ = nullptr;             /// �����_���[
    IShaderLoader* shader_loader_ = nullptr;    /// �V�F�[�_�[���[�_�[
    ITextureLoader* texture_loader_ = nullptr;  /// �e�N�X�`�����[�_�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
/// EOF
