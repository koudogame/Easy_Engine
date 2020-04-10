///
/// @file   message_receiver_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_MESSAGE_RECEIVER_COMPONENT_HEADER_
#define INCLUDED_EGEG_MESSAGE_RECEIVER_COMPONENT_HEADER_
#include "component.hpp"
BEGIN_EGEG
///
/// @class  MessageReceiveComponent
/// @breif  イベントメッセージ受信コンポーネント
///
class MessageReceiveComponent :
    public Component
{
public :
    ///
    /// @brief  メッセージ処理の設定
    ///
    /// @tparam ActorType : 設定者型( 省略可 )
    ///
    /// @param[in] pFunction : メッセージ処理関数
    ///
    template <typename ActorType>
    void setMessageProcessing( void(ActorType::*pFunction)(uint32_t, uint32_t) );

    ///
    /// @breif  イベントメッセージの受け取り
    ///
    /// @param[in] Event   : 発生したイベント
    /// @param[in] Details : 詳細
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


///< メッセージ処理の設定
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
