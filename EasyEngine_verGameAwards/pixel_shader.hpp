///
/// @file   pixel_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   PixelShader
/// @brief   �p�C�v���C���\���I�u�W�F�N�g�u�s�N�Z���V�F�[�_�[�v
/// @details �h���N���X�́A�K���f�X�g���N�^���O�ɃV�F�[�_�[�I�u�W�F�N�g�𐶐����ێ�������̂Ƃ��܂��B<br>
///          �R���X�g���N�^�ł̏����𐄏����܂��B
///
class PixelShader :
    public Shader
{
public :
    virtual ~PixelShader() { shader_->Release(); }
    PixelShader( const PixelShader& Lhs )
    {
        shader_ = Lhs.shader_;
        shader_->AddRef();
    }
    PixelShader& operator=( const PixelShader& Lhs )
    {
        Lhs.shader_->AddRef();

        if( shader_ ) shader_->Release();
        shader_ = Lhs.shader_;
    }
    
protected :
    ID3D11PixelShader* shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
