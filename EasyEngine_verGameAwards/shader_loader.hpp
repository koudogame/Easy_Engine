///
/// @file   shader_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_HEADER_
#include <unordered_map>
#include "loader.hpp"
#include "egeg_utility.hpp"
BEGIN_EGEG
///
/// @class  ShaderLoader
/// @brief  �V�F�[�_�[���[�_�[
///
class ShaderLoader :
    public Loader
{
public :
    using ReturnValue = DetailedReturnValue<bool>;

    ShaderLoader( const std::shared_ptr<RenderingEngine>& Engine ) :
        Loader( Engine )
    {}

    ///
    /// @brief  ���_�V�F�[�_�[�̓ǂݍ���
    ///
    /// @param[in] FileName          : �R���p�C���ς݃V�F�[�_�[�t�@�C����
    /// @param[in] InputElementDescs : ���_���̓��C�A�E�g���\������z��
    /// @param[in] NumElements       : InputElementDescs�z��̗v�f��
    /// @param[out] OutShader        : ���������V�F�[�_�[�I�u�W�F�N�g���i�[����|�C���^
    /// @param[out] OutInputLayout   : �����������_���̓��C�A�E�g�I�u�W�F�N�g���i�[����|�C���^
    ///
    /// @return �ǂݍ��ݐ���[ true ]�@�ǂݍ��ݎ��s[ false ]
    ///
    ReturnValue load( const TCHAR* FileName, const D3D11_INPUT_ELEMENT_DESC* InputElementDescs, size_t NumElements, ID3D11VertexShader** OutShader, ID3D11InputLayout** OutInputLayout );
    ///
    /// @brief  �W�I���g���V�F�[�_�[�̓ǂݍ���
    ///
    /// @param[in] FileName   : �R���p�C���ς݃V�F�[�_�[�t�@�C����
    /// @param[out] OutShader : ���������V�F�[�_�[�I�u�W�F�N�g���i�[����|�C���^
    ///
    /// @return �ǂݍ��ݐ���[ true ]�@�ǂݍ��ݎ��s[ false ]
    ///
    ReturnValue load( const TCHAR* FileName, ID3D11GeometryShader** OutShader );
    ///
    /// @brief  �s�N�Z���V�F�[�_�[�̓ǂݍ���
    ///
    /// @param[in] FileName : �R���p�C���ς݃V�F�[�_�[�t�@�C����
    /// @param[out] OutShader : ���������V�F�[�_�[�I�u�W�F�N�g���i�[����|�C���^
    ///
    /// @return �ǂݍ��ݐ���[ true ]�@�ǂݍ��ݎ��s[ false ]
    ///
    ReturnValue load( const TCHAR* FileName, ID3D11PixelShader** OutShader );
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_HEADER_
/// EOF
