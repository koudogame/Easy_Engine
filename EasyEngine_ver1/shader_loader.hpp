///
/// @file   shader_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_
#define INCLUDED_EGEG_SHADER_LOADER_
#include <string>
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
BEGIN_EGEG
///
/// @class IShaderLoader
///
/// @brief  �V�F�[�_�[���[�_�[
///
class IShaderLoader
{
public :
    ///
    /// @brief  ���_�V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppVertexShader : �ǂݍ��񂾃V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ���[ true ] �ǂݍ��݂Ɏ��s[ false ]
    ///
    virtual bool loadVertexShader( const std::string& FilePath, IVertexShader** ppVertexShader ) = 0;

    ///
    /// @brief  �W�I���g���V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppGeometryShader : �ǂݍ��񂾃V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ���[ true ] �ǂݍ��݂Ɏ��s[ false ]
    ///
    virtual bool loadGeometryShader( const std::string& FilePath, IGeometryShader** ppGeometryShader ) = 0;

    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppPixelShader : �ǂݍ��񂾃V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ���[ true ] �ǂݍ��݂Ɏ��s[ false ]
    ///
    virtual bool loadPixelShader( const std::string& FilePath, IPixelShader** ppPixelShader ) = 0;

    virtual ~IShaderLoader() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_
/// EOF
