///
/// @file   texture_loader.hpp
/// @author ��
///
/// @brief  �e�N�X�`�����[�_�[
///
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#include "interface.hpp"
#include "texture.hpp"
BEGIN_EGEG
class ITextureLoader :
    public Interface
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
    virtual bool load( const wchar_t* FilePath, ITexture** ppTexture ) = 0;

protected :
    virtual ~ITextureLoader() override = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
/// EOF
