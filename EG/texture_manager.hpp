///
/// @file    texture_manager.hpp
/// @author  ��
///          
/// @brief   �e�N�X�`���Ǘ���
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B<br>
///          ���̃N���X��load�֐����g�p���ēǂݍ��񂾃e�N�X�`���́A<br>
///          ���̃N���X��release�֐����g�p���ĉ�����Ă��������B
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
    /// @brief   �摜��ǂݍ��݂܂��B
    /// @details �L���b�V���ɂȂ��ꍇ�A�V�K�ɓǂݍ��݂܂��B<br>
    ///          �L���b�V���ɂ���ꍇ�A���̃R�s�[��ԋp���܂��B
    ///
    /// @param[in] FilePath : �摜�̃t�@�C���p�X
    /// @param[out] ppOutTexture : �ǂݍ��񂾉摜���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool load( const wchar_t* FilePath, ITexture** ppOutTextur );

    ///
    /// @brief   �摜�̉�����s���܂��B
    /// @details �����̃C���^�[�t�F�C�X�ɂ́A�����nullptr�������܂��B<br>
    ///          �L���b�V������폜�����^�C�~���O�͎Q�Ǝ҂����Ȃ��Ȃ������ł��B
    ///
    /// @param[inout] ppTexture : ����Ώۂ̃e�N�X�`��
    ///
    void release( ITexture** ppTexture );
    

    ~TextureManager()
    {
        p_loader_->release();
    }
private :
    TextureManager();

    ITextureLoader* p_loader_;
    std::unordered_map<const wchar_t*, ITexture*> cache_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
/// EOF
