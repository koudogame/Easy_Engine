// 作成者 : 板場
#include "message_receive_component.hpp"
#include "messenger.hpp"

BEGIN_EGEG
// MessageReceiveComponent : 関数の実装
/*===========================================================================*/
// 初期化
bool MessageReceiveComponent::initialize()
{
    // メッセンジャーに登録
    Messenger::instance()->registerReceiver( this );

    return true;
}
// 終了
void MessageReceiveComponent::finalize()
{
    // メッセンジャーから登録を解除
    Messenger::instance()->unregisterReceiver( this );
}
END_EGEG
// EOF
