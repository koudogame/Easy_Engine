///
/// @file   shader_d3d11.hpp 
/// @author ��
///
/// @brief  D3D11�p�V�F�[�_�[�C���^�[�t�F�C�X
///
#ifndef INCLUDED_EG_EG_SHADER_D3D11_HEADER_
#define INCLUDED_EG_EG_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "shader.hpp"
BEGIN_EGEG
class IShaderD3D11 :
    public IShader
{
public :
    ///
    /// @brief  �p�C�v���C���ɃV�F�[�_�[���Z�b�g����B
    ///
    /// @param[in] pDeviceContext : �V�F�[�_�[�I�u�W�F�N�g���Z�b�g����p�C�v���C��
    ///
    void setShaders( ID3D11DeviceContext* pDeviceContext );

protected :
    virtual ~IShaderD3D11() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_D3D11_HEADER_
/// EOF
