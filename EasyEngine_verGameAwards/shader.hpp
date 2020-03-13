///
/// @file   shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHADER_HEADER_
#define INCLUDED_EGEG_SHADER_HEADER_
#include <d3d11.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  Shader
/// @brief  �V�F�[�_�\�I�u�W�F�N�g���
///
class Shader
{
public :
    virtual ~Shader() = default;

    ///< �p�C�v���C���ɃV�F�[�_�\�I�u�W�F�N�g��ݒ�
    virtual void setShaderOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;
    ///< �p�C�v���C���ɃV�F�[�_�\���\�[�X�r���[��ݒ�
    virtual void setShaderResourceViewsOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;
    ///< �p�C�v���C���ɒ萔�o�b�t�@��ݒ�
    virtual void setConstantBuffersOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;
    ///< �p�C�v���C���ɃT���v���[��ݒ�
    virtual void setSamplersOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;

    ///
    /// @brief  �p�C�v���C���ɃV�F�[�_�[�X�e�[�W��ݒ�
    ///
    /// @param[in] Pipeline : �X�e�[�W��ݒ肷��p�C�v���C��
    ///
    void setShaderStageOnPipeline( ID3D11DeviceContext* Pipeline )
    {
        setShaderOnPipeline( Pipeline );
        setShaderResourceViewsOnPipeline( Pipeline );
        setConstantBuffersOnPipeline( Pipeline );
        setSamplersOnPipeline( Pipeline );
    }
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_HEADER_
/// EOF
