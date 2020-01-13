///
/// @file   pixel_shader_d3d11.hpp
/// @author ��
///
/// @brief  D3D11�p�s�N�Z���V�F�[�_�[
///
#ifndef INCLUDED_EG_EG_PIXEL_SHADER_D3D11_HEADER_
#define INCLUDED_EG_EG_PIXEL_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "pixel_shader.hpp"
BEGIN_EGEG
class PixelShaderD3D11 :
    public IPixelShader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pPixelShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    ///
    PixelShaderD3D11( ID3D11PixelShader* pPixelShader ) :
        p_pixel_shader_( pPixelShader )
    {
        p_pixel_shader_->AddRef();
    }

    ///
    /// @brief  �ێ����Ă���V�F�[�_�[�I�u�W�F�N�g���擾���܂��B
    ///
    /// @return �ێ����Ă���V�F�[�_�\�I�u�W�F�N�g�̃A�h���X
    ///
    ID3D11PixelShader* get() const { return p_pixel_shader_; }

private :
    ~PixelShaderD3D11()
    {
        p_pixel_shader_->Release();
    }

    ID3D11PixelShader* p_pixel_shader_;
};
END_EGEG
#endif  /// !INCLUDED_EG_EG_PIXEL_SHADER_D3D11_HEADER_
/// EOF
