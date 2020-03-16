///
/// @file   pixel_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include <type_traits>
#include <wrl.h>
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   PixelShader
/// @brief   �p�C�v���C���\���I�u�W�F�N�g�u�s�N�Z���V�F�[�_�[�v
/// @details �h���N���X�́A���g�̈����s�N�Z���V�F�[�_�\�t�@�C����<br>
///          static constexpr const char* kPSFileName<br>
///          �Ƃ��Ē�`���ĉ������BShaderLoader�ŗ��p���܂��B
///
class PixelShader :
    public Shader
{
public :
    template <class ShaderType>
    PixelShader( ShaderType&& Shader ) :
        shader_( std::forward<ShaderType>(Shader) )
    {
    }
    virtual ~PixelShader() = default;
    
protected :
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
