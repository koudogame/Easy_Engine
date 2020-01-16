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
    void showDialogBox( const std::string& ) override;
    bool createRenderer( IRenderer** ) override;
    bool createShaderLoader( IShaderLoader** ) override;
    bool createTextureLoader( ITextureLoader** ) override;

private :
    ~PlatformWindows();
    bool initialize();

    HWND h_window_;                             /// �E�B���h�E�n���h��
    D3D_FEATURE_LEVEL feature_level_;           /// �̗p���ꂽDirectX�@�\���x��
    ID3D11Device* p_device_;                    /// D3D�f�o�C�X
    ID3D11DeviceContext* p_immediate_context_;  /// D3D�f�o�C�X�R���e�L�X�g
    IDXGISwapChain* p_swap_chain_;              /// DXGI�X���b�v�`�F�C��
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
/// EOF
