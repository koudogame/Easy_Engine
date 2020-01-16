///
/// @file    system_manager.hpp
/// @author  ��
///          
/// @brief   �V�X�e���}�l�[�W���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
#ifndef INCLUDED_EGEG_SYSTEM_MANAGER_HEADER_
#define INCLUDED_EGEG_SYSTEM_MANAGER_HEADER_
#include "easy_engine.hpp"
#include "platform.hpp"
BEGIN_EGEG
class SystemManager
{
public :
    ///
    /// @brief  �C���X�^���X�ւ̃A�N�Z�X
    ///
    /// @return �C���X�^���X
    ///
    static SystemManager* instance() { return instance_; }

    ///
    /// @brief  �_�C�A���O�{�b�N�X�̕\��
    ///
    /// @param[in] Message : �\�����郁�b�Z�[�W
    ///
    void showDialogBox( const std::string& Message );

    ///
    /// @brief  �C���X�^���X�̐���
    ///
    /// @param[in] Creator : ������
    /// @param[in] pPlatform : �g�p����v���b�g�t�H�[��
    ///
    static void create( const EasyEngine& Creator, IPlatform* pPlatform );
    ///
    /// @brief  �C���X�^���X�̔j��
    ///
    /// @param[in] Deleter : �j����
    ///
    static void destroy( const EasyEngine& Deleter );

    SystemManager( const SystemManager& ) = delete;
    SystemManager& operator=( const SystemManager& ) = delete;
private :
    SystemManager( IPlatform* );
    ~SystemManager();
    static SystemManager* instance_;
    IPlatform* p_platform_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SYSTEM_MANAGER_HEADER_
/// EOF
