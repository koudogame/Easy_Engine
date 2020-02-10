///
/// @file   messenger.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_MESSENGER_HEADER_
#define INCLUDED_EGEG_MESSENGER_HEADER_
#include <list>
#include "message_receive_component.hpp"
BEGIN_EGEG
///
/// @class   Messenger
/// @brief   イベントメッセージ通達者
///          
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
class Messenger
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static Messenger* instance() { static Messenger i; return &i; }

    ///
    /// @brief  イベントメッセージ受信コンポーネントの登録
    ///
    /// @param[in] pReceiver : 受信コンポーネント
    ///
    void registerReceiver( MessageReceiveComponent* pReceiver ) { receiver_.push_back( pReceiver ); }
    ///
    /// @brief  イベントメッセージ受信コンポーネントの登録解除
    ///
    /// @param[in] pReceiver : 削除するコンポーネント
    ///
    void unregisterReceiver( MessageReceiveComponent* pReceiver ) { receiver_.remove( pReceiver ); }

    ///
    /// @brief  イベントメッセージ発効
    ///
    /// @param[in] Event   : 発効するイベントメッセージ
    /// @param[in] Details : イベント詳細
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
