///
/// @file   vertex_shader_d3d11.hpp
/// @author ��
///
/// @brief  DirectX11�p���_�V�F�[�_�[
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_D3D11_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "vertex_shader.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class VertexShaderD3D11 :
    public IVertexShader
{
public :
    ///< ���_���̓��C�A�E�g��`
    static constexpr D3D11_INPUT_ELEMENT_DESC kVertexInputLayout[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            0,
            sizeof Float4,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            sizeof Float4 + sizeof Float2,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
    };

    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pVertexShader : �ێ�����V�F�[�_�[�I�u�W�F�N�g
    /// @param[iu] pInputLayout  : ���_���̓��C�A�E�g�I�u�W�F�N�g
    ///
    VertexShaderD3D11( ID3D11VertexShader* pVertexShader,
                       ID3D11InputLayout*  pInputLayout ) :
        p_shader_( pVertexShader ),
        p_layout_( pInputLayout )
    {
        p_shader_->AddRef();
        p_layout_->AddRef();
    }

    ///
    /// @brief   �V�F�[�_�[�I�u�W�F�N�g�̎擾
    ///
    /// @return  �V�F�[�_�[�I�u�W�F�N�g
    ///
    ID3D11VertexShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

    ///
    /// @brief  ���_���̓��C�A�E�g�̎擾
    ///
    /// @return ���_���̓��C�A�E�g
    ///
    ID3D11InputLayout*  getLayout() const { p_layout_->AddRef(); return p_layout_; }

private :
    ~VertexShaderD3D11()
    {
        p_layout_->Release();
        p_shader_->Release();
    }
    ID3D11VertexShader* p_shader_;  /// �V�F�[�_�[
    ID3D11InputLayout*  p_layout_;  /// ���_���̓��C�A�E�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_D3D11_HEADER_
/// EOF
