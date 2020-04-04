///
/// @file   shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHADER_HEADER_
#define INCLUDED_EGEG_SHADER_HEADER_

#include <d3d11.h>
#include "material.hpp"

BEGIN_EGEG

///
/// @class  Shader
/// @brief  �V�F�[�_�\�I�u�W�F�N�g���
///
class Shader
{
public :
    Shader() = default;
    virtual ~Shader() = default;
    Shader( const Shader& ) = default;
    Shader& operator=( const Shader& ) = default;
    Shader( Shader&& ) = default;
    Shader& operator=( Shader&& ) = default;

    ///< �p�C�v���C���ɃV�F�[�_�\��ݒ�
    virtual void setShaderOnPipeline( ID3D11DeviceContext* ) = 0;
    ///< �p�C�v���C���ɃV�F�[�_�\���\�[�X��ݒ�
    virtual void setShaderResourcesOnPipeline( ID3D11DeviceContext* ) = 0;
    ///< �p�C�v���C���ɒ萔�o�b�t�@��ݒ�
    virtual void setConstantBuffersOnPipeline( ID3D11DeviceContext* ) = 0;
    ///< �p�C�v���C���ɃT���v���[��ݒ�
    virtual void setSamplersOnPipeline( ID3D11DeviceContext* ) = 0;

    ///< �V�F�[�_�[�Ƀ}�e���A�����Z�b�g
    virtual void setMaterial( const Material& Material ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_HEADER_
/// EOF
