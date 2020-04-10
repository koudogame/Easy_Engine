///
/// @file   message_receiver_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_MESSAGE_RECEIVER_COMPONENT_HEADER_
#define INCLUDED_EGEG_MESSAGE_RECEIVER_COMPONENT_HEADER_
#include "component.hpp"
BEGIN_EGEG
///
/// @class  MessageReceiveComponent
/// @breif  �C�x���g���b�Z�[�W��M�R���|�[�l���g
///
class MessageReceiveComponent :
    public Component
{
public :
    ///
    /// @brief  ���b�Z�[�W�����̐ݒ�
    ///
    /// @tparam ActorType : �ݒ�Ҍ^( �ȗ��� )
    ///
    /// @param[in] pFunction : ���b�Z�[�W�����֐�
    ///
    template <typename ActorType>
    void setMessageProcessing( void(ActorType::*pFunction)(uint32_t, uint32_t) );

    ///
    /// @breif  �C�x���g���b�Z�[�W�̎󂯎��
    ///
    /// @param[in] Event   : ���������C�x���g
    /// @param[in] Details : �ڍ�
    ///
    void messageProcessing( uint32_t Event, uint32_t Details ) { if( f_callback_ ) f_callback_( Event, Details ); }

/*-----------------------------------------------------------------*/
// Component
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

private :
    std::function<void(uint32_t, uint32_t)> f_callback_;
};


///< ���b�Z�[�W�����̐ݒ�
template <typename ActorType>
void MessageReceiveComponent::setMessageProcessing( void(ActorType::*pFunc)(uint32_t, uint32_t) )
{
    f_callback_ = 
        std::extraction<void(uint32_t, uint32_t)>(
            pFunc,
            owner_,
            std::placeholders::_1,
            std::placeholders::_2
        );
}
END_EGEG
#endif /// !INCLUDED_EGEG_MESSAGE_RECEIVER_COMPONENT_HEADER_
/// EOF
