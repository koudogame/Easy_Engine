///
/// @file   geometry_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   GeometryShader
/// @brief   �p�C�v���C���\���I�u�W�F�N�g�u�W�I���g���V�F�[�_�[�v
/// @details �h���N���X�́A�K���f�X�g���N�^���O�ɃV�F�[�_�[�I�u�W�F�N�g�𐶐����ێ�������̂Ƃ��܂��B<br>
///          �R���X�g���N�^�ł̏����𐄏����܂��B
///
class GeometryShader :
    public Shader
{
public :
    virtual ~GeometryShader() { shader_->Release(); }
    GeometryShader( const GeometryShader& Lhs )
    {
        shader_ = Lhs.shader_;
        shader_->AddRef();
    }
    GeometryShader& operator=( const GeometryShader& Lhs )
    {
        Lhs.shader_->AddRef();

        if( shader_ ) shader_->Release();
        shader_ = Lhs.shader_;
    }

private :
    ID3D11GeometryShader* shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
