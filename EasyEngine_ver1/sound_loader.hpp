///
/// @file   sound_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SOUND_LOADER_HEADER_
#define INCLUDED_EGEG_SOUND_LOADER_HEADER_
#include <string>
#include "sound.hpp"
BEGIN_EGEG
///
/// @class ISoundLoader
///
/// @brief  �T�E���h���[�_�[
///
class ISoundLoader
{
public :
    ///
    /// @brief  �T�E���h�f�[�^�̓ǂݍ���
    ///
    /// @param[in] FilePath : �ǂݍ��ރT�E���h�̃t�@�C���p�X
    /// @param[in] ppSound : �ǂݍ��񂾃T�E���h��ێ�����C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��ݐ���[ true ] �ǂݍ��ݎ��s[ false ]
    ///
    virtual bool load( const std::wstring& FilePath, ISound** ppSound ) = 0;

    virtual ~ISoundLoader() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SOUND_LOADER_HEADER_
/// EOF
