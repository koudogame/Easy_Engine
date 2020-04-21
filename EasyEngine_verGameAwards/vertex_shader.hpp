///
/// @file   vertex_shader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_HEADER_

#include <type_traits>
#include <vector>
#include <wrl.h>
#include "shader.hpp"
#include "result.hpp"
#include "vertex.hpp"

BEGIN_EGEG

struct BindedVertexData
{
    std::vector<ID3D11Buffer*> buffers;
    std::vector<UINT>          strides;
    std::vector<UINT>          offsets;
};

///
/// @class   VertexShader
/// @brief   �p�C�v���C���\���I�u�W�F�N�g�u���_�V�F�[�_�\�v
/// @details �h���N���X�́A���g�̈������_�V�F�[�_�\�t�@�C���ƒ��_���̓��C�A�E�g�����ꂼ��<br>
///          static constexpr D3D11_INPUT_ELEMENT_DESC kInputElementDescs[]<br>
///          static constexpr const char* kVSFileName<br>
///          �Ƃ��Ē�`���ĉ������BShaderLoader�ŗ��p���܂��B
///
class VertexShader :
    public Shader
{
public :
    template <class ShaderType,
              class InputLayoutType>
    VertexShader( ShaderType&& Shader, InputLayoutType&& InputLayout ) :
        shader_( std::forward<ShaderType>(Shader) ),
        input_layout_( std::forward<InputLayoutType>(InputLayout) )
    {
    }
    virtual ~VertexShader() = default;

    ///< ���_�̓��̓��C�A�E�g�Ƀo�C���h����I�u�W�F�N�g���擾����
    virtual DetailedResult<BindedVertexData> bindVertices( const Vertex& Vertices ) const = 0;

    ///< �p�C�v���C���ɒ��_���̓��C�A�E�g���Z�b�g
    void setInputLayoutOnPipeline( ID3D11DeviceContext* ImmediateContext ) 
    {
        ImmediateContext->IASetInputLayout( input_layout_.Get() );
    }

protected :
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_ = nullptr;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  input_layout_ = nullptr;
};

END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_HEADER_
/// EOF
