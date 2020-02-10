// 作成者 : 板場
#include "messenger.hpp"

BEGIN_EGEG
// Messenger : 関数の実装
/*===========================================================================*/
// メッセージ発効
void Messenger::postEventMessage( uint32_t Event, uint32_t Details )
{
    for( auto& receiver : receiver_ )
    {
        receiver->messageProcessing( Event, Details );
    }
}
END_EGEG
// EOF
