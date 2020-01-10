///
/// @file    texture_manager.hpp
/// @author  ��
///          
/// @brief   �e�N�X�`���Ǘ���
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B
///
#ifndef INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
#include <unordered_map>
#include "texture_loader.hpp"
BEGIN_EG_EG
class TextureManager
{
public :
    static TextureManager* instance() { static TextureManager i; return&i; }

    ///
    /// @brief   �摜���擾���܂��B
    /// @details �L���b�V���ɉ摜���Ȃ��ꍇ(�V�K�̎擾�̏ꍇ)�摜��ǂݍ��݂܂��B<br>
    ///          �L���b�V���ɉ摜������ꍇ�A���̃R�s�[��ԋp���܂��B
    ///
    /// @param[in] FilePath : �摜�̃t�@�C���p�X
    /// @param[out] ppOutTexture : �ǂݍ��񂾉摜���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �擾�ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B�ԋp���܂��B
    ///
    bool get( const wchar_t* FilePath, ITexture** ppOutTextur );

private :
    TextureManager() = default;

    ITextureLoader* loader_ = nullptr;
    std::unordered_map<const wchar_t*, ITexture*> cache_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
/// EOF
