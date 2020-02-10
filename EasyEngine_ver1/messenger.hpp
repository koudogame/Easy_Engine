///
/// @file   messenger.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_MESSENGER_HEADER_
#define INCLUDED_EGEG_MESSENGER_HEADER_
#include <list>
#include "message_receive_component.hpp"
BEGIN_EGEG
///
/// @class   Messenger
/// @brief   �C�x���g���b�Z�[�W�ʒB��
///          
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
class Messenger
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static Messenger* instance() { static Messenger i; return &i; }

    ///
    /// @brief  �C�x���g���b�Z�[�W��M�R���|�[�l���g�̓o�^
    ///
    /// @param[in] pReceiver : ��M�R���|�[�l���g
    ///
    void registerReceiver( MessageReceiveComponent* pReceiver ) { receiver_.push_back( pReceiver ); }
    ///
    /// @brief  �C�x���g���b�Z�[�W��M�R���|�[�l���g�̓o�^����
    ///
    /// @param[in] pReceiver : �폜����R���|�[�l���g
    ///
    void unregisterReceiver( MessageReceiveComponent* pReceiver ) { receiver_.remove( pReceiver ); }

    ///
    /// @brief  �C�x���g���b�Z�[�W����
    ///
    /// @param[in] Event   : ��������C�x���g���b�Z�[�W
    /// @param[in] Details : �C�x���g�ڍ�
    ///
    void postEventMessage( uint32_t Event, uint32_t Details );

private :
    std::list<MessageReceiveComponent*> receiver_;

    Messenger() = default;
    Messenger( const Messenger& ) = delete;
    Messenger& operator=( const Messenger& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESSENGER_HEADER_
/// EOF
