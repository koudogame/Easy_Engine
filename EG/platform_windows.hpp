///
/// @file    platform_windows.hpp
/// @author  ��
///          
/// @brief   �v���b�g�t�H�[���uWindows�v
/// @details �J�������g��release�֐��݂̂ōs������<br>
///          �f�X�g���N�^�̌Ăяo���ɐ����������Ă��܂��B
///
#ifndef INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
#define INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
#include <Windows.h>
#include <d3d11.h>
#include "platform.hpp"
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class PlatformWindows :
    public IPlatform
{
public :
    static IPlatform* create();

// IPlatform
/*-----------------------------------------------------------------*/
    void gameLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const char * ) override;

    IRenderer* getRenderer() const override { return p_renderer_; }
    IShaderLoader* getShaderLoader() const override { return p_shader_loader_; }
    ITextureLoader* getTextureLoader() const override { return p_texture_loader_; }

private :
    bool initialize();          /// ���������� * �������ɌĂяo���B
    ~PlatformWindows();
    bool initializeWindow();    /// �E�B���h�E������
    bool initializeDirect3D();  /// Direct3D������

    HWND window_handle_;                /// �E�B���h�E�n���h��
    D3D_FEATURE_LEVEL feature_level_;   /// D3D�@�\���x��
    IRenderer* p_renderer_;             /// �����_���[
    IShaderLoader* p_shader_loader_;    /// �V�F�[�_�[���[�_�[
    ITextureLoader* p_texture_loader_;  /// �e�N�X�`�����[�_�[
};
END_EGEG
#endif /// !INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
/// EOF
