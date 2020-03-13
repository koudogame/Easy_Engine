///
/// @file   vertex_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#include "shader.hpp"
#include "vertex_binder.hpp"
BEGIN_EGEG
///
/// @class   VertexShader
/// @brief   �p�C�v���C���\���I�u�W�F�N�g�u���_�V�F�[�_�\�v
/// @details �h���N���X�́A�K���f�X�g���N�^���O�ɃV�F�[�_�[�I�u�W�F�N�g�A�y�ѓ��̓��C�A�E�g�I�u�W�F�N�g�𐶐����ێ�������̂Ƃ��܂��B<br>
///          �R���X�g���N�^�ł̏����𐄏����܂��B
///
class VertexShader :
    public Shader
{
public :
    virtual ~VertexShader() { shader_->Release(); input_layout_->Release(); }
    VertexShader( const VertexShader& Lhs )
    {
        shader_ = Lhs.shader_;
        shader_->AddRef();
        input_layout_ = Lhs.input_layout_;
        input_layout_->AddRef();
    }
    VertexShader& operator=( const VertexShader& Lhs )
    {
        Lhs.shader_->AddRef();
        Lhs.input_layout_->AddRef();

        if( shader_ ) shader_->Release();
        if( input_layout_ ) input_layout_->Release();
        shader_ = Lhs.shader_;
        input_layout_ = Lhs.input_layout_;
    }

    ///< ���_�̓��̓��C�A�E�g�Ƀo�C���h����I�u�W�F�N�g���擾����
    virtual VertexBinder getVertexBinder() const = 0;

protected :
    ID3D11VertexShader* shader_ = nullptr;
    ID3D11InputLayout*  input_layout_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_HEADER_
/// EOF
