///
/// @file   texture_loader.hpp
/// @author ��
///
/// @brief  �e�N�X�`�����\�[�X���[�_�[�̃C���^�[�t�F�C�X
/// 
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#include "interface.hpp"
#include "texture.hpp"
BEGIN_EG_EG
class ITextureLoader :
    public Interface
{
public :
    ///
    /// @brief  �e�N�X�`���̃��[�h
    ///
    /// @param[in] FilePath : ���\�[�X�̃t�@�C���p�X
    /// @param[out] ppOutTexture : ���[�h�����e�N�X�`�����󂯎��C���^�[�t�F�C�X
    ///
    /// @return ���[�h�ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    virtual bool load( const wchar_t* FilePath, ITexture** ppOutTexture ) = 0;

protected :
    ~ITextureLoader() = default;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
///  EOF
