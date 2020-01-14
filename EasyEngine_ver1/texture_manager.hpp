///
/// @file    texture_manager.hpp
/// @author  ��
///          
/// @brief   �e�N�X�`���}�l�[�W���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B<br>
///          ��x�ǂݍ��񂾃e�N�X�`���̓L���b�V���ɕۑ�����܂��B<br>
///          ���̃N���X�̔j�����A�L���b�V���ɂ���e�N�X�`���͊J������܂��B<br>
///          ���̃N���X���g�p���ēǂݍ��񂾃e�N�X�`���́A�K�����̃N���X�ŊJ�����Ă��������B
///
#ifndef INCLUDED_TEXTURE_MANAGER_HEADER_
#define INCLUDED_TEXTURE_MANAGER_HEADER_
#include <unordered_map>
#include "easy_engine.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class TextureManager
{
public :
    ///
    /// @brief  �C���X�^���X�ւ̃A�N�Z�X
    ///
    /// @return �C���X�^���X
    ///
    static TextureManager* instance() { return instance_; }

    ///
    /// @brief   �e�N�X�`���̃��[�h
    /// @details �L���b�V���ɓǂݍ��ݍς݃e�N�X�`��������ꍇ�A���̃R�s�[��ԋp���܂��B
    ///
    /// @param[in] FilePath : �ǂݍ��ރe�N�X�`���̃t�@�C���p�X
    /// @param[out] ppTexture : �ǂݍ��񂾃e�N�X�`�����󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��ݐ���[ true ] �ǂݍ��ݎ��s[ false ]
    ///
    bool load( const wchar_t* FilePath, ITexture** ppTexture );
    ///
    /// @brief   �e�N�X�`���̊J��
    /// @details �Q�Ǝ҂̃f�N�������g���s���A�Q�Ǝ҂����Ȃ��Ȃ������_�ŊJ�����܂��B<br>
    ///          �����Ŏ󂯎�����C���^�[�t�F�C�X�ɂ́Anullptr���������܂��B
    ///
    /// @param[inout] ppTexture : �J������e�N�X�`��
    ///
    void release( ITexture** ppTexture );

    ///
    /// @brief   �C���X�^���X�̐���
    ///
    /// @param[in] pCreator : ������
    /// @param[in] pTextureLoader : �g�p����e�N�X�`�����[�_�[
    ///
    static void create( EasyEngine* pCreator, ITextureLoader* pTextureLoader );
    ///
    /// @brief  �C���X�^���X�̔j��
    ///
    /// @param[in] pDeleter : �j����
    ///
    static void destroy( EasyEngine* pDeleter );
    ~TextureManager();
private :
    TextureManager( ITextureLoader* );
    static TextureManager* instance_;
    ITextureLoader* p_loader_;
    std::unordered_map<const wchar_t*, ITexture*> cache_;   /// �e�N�X�`�����\�[�X�̃L���b�V��
};
END_EGEG
#endif /// !INCLUDED_TEXTURE_MANAGER_HEADER_
/// EOF
