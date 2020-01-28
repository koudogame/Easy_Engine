///
/// @file   geometry_shader_d3d11.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_D3D11_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "geometry_shader.hpp"
BEGIN_EGEG
///
/// @class  GeometryShaderD3D11
///
/// @brief  DirectX11�p�W�I���g���V�F�[�_�[
///
class GeometryShaderD3D11 :
    public IGeometryShader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pGeometryShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    ///
    GeometryShaderD3D11( ID3D11GeometryShader* pGeometryShader) :
        p_shader_( pGeometryShader )
    {
        p_shader_->AddRef();
    }

    ///
    /// @brief   �V�F�[�_�[�I�u�W�F�N�g�̎擾
    ///
    /// @return  �V�F�[�_�[�I�u�W�F�N�g
    ///
    ID3D11GeometryShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

private :
    ~GeometryShaderD3D11()
    {
        p_shader_->Release();
    }
    ID3D11GeometryShader* p_shader_;    /// �V�F�[�_�[�I�u�W�F�N�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_D3D11_HEADER_
/// EOF
