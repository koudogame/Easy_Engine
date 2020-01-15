///
/// @file    texture_loader.hpp
/// @author  ��
///          
/// @brief   �e�N�X�`�����\�[�X���[�_�[�̊��N���X
/// @details �h���N���X�� loadFromFile���������ĉ������B
/// 
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#include <unordered_map>
#include "interface.hpp"
BEGIN_EGEG
class ITexture;
class ITextureLoader :
    public SharedObject
{
public :
    ///
    /// @brief   �e�N�X�`���̃��[�h
    /// @details �L���b�V���ɂ���ꍇ�A�R�s�[���邽�߃��[�h���Ԃ͂�����܂���B
    ///          �L���b�V���ɂȂ��ꍇ�A���[�h���Ԃ�������܂��B
    ///
    /// @param[in] FilePath : ���\�[�X�̃t�@�C���p�X
    /// @param[out] ppOutTexture : ���[�h�����e�N�X�`�����󂯎��C���^�[�t�F�C�X
    ///
    /// @return ���[�h�ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool load( const wchar_t* FilePath, ITexture** ppOutTexture );

    ///
    /// @brief   �e�N�X�`�����\�[�X�̉���ʒm���󂯎��܂��B
    /// @details �����̃e�N�X�`�����L���b�V���ɑ��݂�����A�L���b�V������폜���܂��B
    ///
    /// @param[in] Notifier : �����ʒm����e�N�X�`��
    ///
    void notifyReleaseTexture( ITexture* Notifier );
protected :
    ///
    /// @brief  �t�@�C������e�N�X�`�������[�h����
    ///
    /// @param[in] Path : ���\�[�X�̃t�@�C���p�X
    /// @param[out] ppOut : ���[�h�����e�N�X�`�����Z�b�g����C���^�[�t�F�C�X
    ///
    /// @return ���[�h����[ true ] ���[�h���s[ false ]
    ///
    virtual bool loadFromFile( const wchar_t* Path, ITexture** ppOut ) = 0;
    virtual ~ITextureLoader() = default;

private :
    std::unordered_map<const wchar_t*, ITexture*> cache_;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
///  EOF
