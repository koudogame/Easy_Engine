///
/// @file    sound_manager.hpp
/// @author  ��
///          
/// @brief   �T�E���h�}�l�[�W���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B<br>
///          ���̃N���X���g�p���ēǂݍ��񂾃T�E���h�́A�K�����̃N���X�ŊJ�����Ă��������B
///
#ifndef INCLUDED_EGEG_SOUND_MANAGER_HEADER_
#define INCLUDED_EGEG_SOUND_MANAGER_HEADER_
#include "easy_engine.hpp"
#include "sound_loader.hpp"
BEGIN_EGEG
class SoundManager
{
public :
    ///
    /// @brief  �C���X�^���X�ւ̃A�N�Z�X
    ///
    /// @return �C���X�^���X
    ///
    static SoundManager* instance() { return instance_; }

    ///
    /// @brief  �C���X�^���X�̐���
    ///
    /// @param[in] Creator : ������
    /// @param[in] pLoader : �g�p����T�E���h���[�_�[
    ///
    static void create( const EasyEngine& Creator, ISoundLoader* pLoader );
    ///
    /// @brief  �C���X�^���X�̔j��
    ///
    /// @param[in] Deleter : �j����
    ///
    static void destroy( const EasyEngine& Deleter );

private :
    SoundManager( ISoundLoader* );
    ~SoundManager();
    SoundManager( const SoundManager& ) = delete;
    SoundManager& operator=( const SoundManager& ) = delete;
    static SoundManager* instance_;

    ISoundLoader* p_loader_;    /// �g�p����T�E���h���[�_�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_SOUND_MANAGER_HEADER_
/// EOF
