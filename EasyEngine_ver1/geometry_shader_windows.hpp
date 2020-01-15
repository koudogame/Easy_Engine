///
/// @file   geometry_shader_windows.hpp
/// @author ��
///
/// @brief  Windows�p�W�I���g���V�F�[�_�[
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "geometry_shader.hpp"
BEGIN_EGEG
class GeometryShaderWindows :
    public IGeometryShader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pGeometryShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    ///
    GeometryShaderWindows( ID3D11GeometryShader* pGeometryShader) :
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
    ~GeometryShaderWindows()
    {
        p_shader_->Release();
    }
    ID3D11GeometryShader* p_shader_;    /// �V�F�[�_�[�I�u�W�F�N�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_WINDOWS_HEADER_
/// EOF
