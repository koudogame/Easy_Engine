///
/// @file   vertex_shader_windows.hpp
/// @author ��
///
/// @brief  Windows�p���_�V�F�[�_�[
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "vertex_shader.hpp"
BEGIN_EGEG
class VertexShaderWindows :
    public IVertexShader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pVertexShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    ///
    VertexShaderWindows( ID3D11VertexShader* pVertexShader ) :
        p_shader_( pVertexShader )
    {
        p_shader_->AddRef();
    }

    ///
    /// @brief   �V�F�[�_�[�I�u�W�F�N�g�̎擾
    ///
    /// @return  �V�F�[�_�[�I�u�W�F�N�g
    ///
    ID3D11VertexShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

private :
    ~VertexShaderWindows()
    {
        p_shader_->Release();
    }
    ID3D11VertexShader* p_shader_;  /// �V�F�[�_�[�I�u�W�F�N�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_WINDOWS_HEADER_
/// EOF
