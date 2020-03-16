///
/// @file   geometry_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include <type_traits>
#include <wrl.h>
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   GeometryShader
/// @brief   �p�C�v���C���\���I�u�W�F�N�g�u�W�I���g���V�F�[�_�[�v
/// @details �h���N���X�́A���g�̈����W�I���g���V�F�[�_�\�t�@�C����<br>
///          static constexpr const char* kGSFileName<br>
///          �Ƃ��Ē�`���ĉ������BShaderLoader�ŗ��p���܂��B
///
class GeometryShader :
    public Shader
{
public :
    template <class ShaderType>
    GeometryShader( ShaderType&& Shader ) :
        shader_( std::forward<ShaderType>(Shader) )
    {
    }
    virtual ~GeometryShader() = default;

private :
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
