///
/// @file   shader_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_HEADER_

#include <vector>
#include <d3d11.h>
#include "rendering_manager_child.hpp"
#include "return_value.hpp"

BEGIN_EGEG

///
/// @class ShaderLoader
/// @brief �V�F�[�_�[���[�_�[
///
class ShaderLoader :
    public RenderingManagerChild
{
public :
    using RetTy = DetailedReturnValue<bool>;

    ///
    /// @brief ���_�V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] CompiledShaderFilePath : �ǂݍ��ރR���p�C���ς݃V�F�[�_�\�t�@�C���̃p�X
    /// @param[in] InputDescs             : ���_���̓��C�A�E�g�z��
    /// @param[out] VSOUt                 : ���_�V�F�[�_�\�o�͐�
    /// @param[out] ILOut                 : ���_���̓��C�A�E�g�o�͐�
    ///
    /// @return true:�����@false:���s
    ///
    RetTy loadVertexShader( 
        const std::string& CompiledShaderFilePath, 
        const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputDescs,
        ID3D11VertexShader** VSOut, ID3D11InputLayout** ILOut ) const;

    ///
    /// @brief  �W�I���g���V�F�[�_�[�̃��[�h
    ///
    /// @param[in] CompiledShaderFilePath : �ǂݍ��ރR���p�C���σV�F�[�_�\�t�@�C���p�X
    /// @param[out] GSOut                 : �W�I���g���V�F�[�_�[�o�͐�
    ///
    /// @return true:�����@false:���s
    ///
    RetTy loadGeometryShader( 
        const std::string& CompiledShaderFilePath,
        ID3D11GeometryShader** GSOut ) const;

    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̃��[�h
    ///
    /// @param[in] CompiledShaderFilePath : �ǂݍ��ރR���p�C���ς݃V�F�[�_�\�t�@�C���p�X
    /// @param[out] PSOut                 : �s�N�Z���V�F�[�_�\�o�͐�
    ///
    /// @return true:�����@false:���s
    ///
    RetTy loadPixelShader(
        const std::string& CompiledShaderFilePath,
        ID3D11PixelShader** PSOut ) const;
    
    ///
    /// @brief  �R���s���[�g�V�F�[�_�\�̃��[�h
    ///
    /// @param[in] CompiledShaderFilePath : �ǂݍ��ރR���p�C���ς݃V�F�[�_�\�t�@�C���p�X
    /// @param[out] CSOut                 : �R���s���[�g�V�F�[�_�\�o�͐�
    ///
    /// @return true:�����@false:���s
    ///
    RetTy loadComputeShader(
        const std::string& CompiledShaderFilePath,
        ID3D11ComputeShader** CSOut ) const;


    struct BinaryData
    {
        BinaryData() = default;
        ~BinaryData() { delete[] bytecode; }
        BinaryData( BinaryData&& Rhs ) noexcept:
            length{ Rhs.length },
            bytecode{ Rhs.bytecode }
        {
            Rhs.length = 0;
            Rhs.bytecode = nullptr;
        }
        size_t length{ 0 };
        char* bytecode{ nullptr };
    };
private :
    bool createIL( const BinaryData&, const std::vector<D3D11_INPUT_ELEMENT_DESC>&, ID3D11InputLayout** ) const;
    bool createVS( const BinaryData&, ID3D11VertexShader** ) const;
    bool createGS( const BinaryData&, ID3D11GeometryShader** ) const;
    bool createPS( const BinaryData&, ID3D11PixelShader** ) const;
    bool createCS( const BinaryData&, ID3D11ComputeShader** ) const;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_HEADER_
/// EOF
