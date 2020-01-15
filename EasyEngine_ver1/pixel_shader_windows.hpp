///
/// @file   pixel_shader_windows.hpp
/// @author ��
///
/// @brief  Windows�p�s�N�Z���V�F�[�_�[
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "pixel_shader.hpp"
BEGIN_EGEG
class PixelShaderWindows :
    public IPixelShader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pPixelShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    ///
    PixelShaderWindows( ID3D11PixelShader* pPixelShader ) :
        p_shader_( pPixelShader )
    {
        p_shader_->AddRef();
    }

    ///
    /// @brief  �V�F�[�_�[�I�u�W�F�N�g�̎擾
    ///
    /// @return �V�F�[�_�[�I�u�W�F�N�g
    ///
    ID3D11PixelShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

private :
    ~PixelShaderWindows()
    {
        p_shader_->Release();
    }
    ID3D11PixelShader* p_shader_;   /// �V�F�[�_�[�I�u�W�F�N�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_WINDOWS_HEADER_
/// EOF
