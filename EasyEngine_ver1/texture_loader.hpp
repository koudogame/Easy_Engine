///
/// @file   texture_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#include <string>
#include "texture.hpp"
BEGIN_EGEG
///
/// @class ITextureLoader
///
/// @brief  �e�N�X�`�����[�_�[
///
class ITextureLoader
{
public :
    ///
    /// @brief  �e�N�X�`�����\�[�X�̓ǂݍ���
    ///
    /// @param[in] FilePath : �ǂݍ��ރe�N�X�`���̃t�@�C���p�X
    /// @param[out] ppTexture : �ǂݍ��񂾃e�N�X�`����ێ�����C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��ݐ���[ true ] �ǂݍ��ݎ��s[ false ]
    ///
    virtual bool load( const std::wstring& FilePath, ITexture** ppTexture ) = 0;

    virtual ~ITextureLoader() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
/// EOF
