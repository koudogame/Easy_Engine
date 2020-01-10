///
/// @file   vertex_shader_d3d11.hpp
/// @author ��
///
/// @brief  D3D11�p���_�V�F�[�_�[
///
#ifndef INCLUDED_EG_EG_VERTEX_SHADER_D3D11_HEADER_
#define INCLUDED_EG_EG_VERTEX_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "vertex_shader.hpp"
BEGIN_EG_EG
class VertexShaderD3D11 :
    public IVertexShader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pVertexShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    ///
    VertexShaderD3D11( ID3D11VertexShader* pVertexShader ) :
        p_vertex_shader_( pVertexShader )
    {
        p_vertex_shader_->AddRef();
    }

    ///
    /// @brief  �ێ����Ă���V�F�[�_�[�I�u�W�F�N�g���擾���܂��B
    ///
    /// @return �ێ����Ă���V�F�[�_�[�I�u�W�F�N�g�̃A�h���X
    ///
    ID3D11VertexShader* get() const { return p_vertex_shader_; }

private :
    ~VertexShaderD3D11()
    {
        p_vertex_shader_->Release();
    }

    ID3D11VertexShader* p_vertex_shader_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_VERTEX_SHADER_D3D11_HEADER_
/// EOF
