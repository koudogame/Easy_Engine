// �쐬�� : ��
#include "messenger.hpp"

BEGIN_EGEG
// Messenger : �֐��̎���
/*===========================================================================*/
// ���b�Z�[�W����
void Messenger::postEventMessage( uint32_t Event, uint32_t Details )
{
    for( auto& receiver : receiver_ )
    {
        receiver->messageProcessing( Event, Details );
    }
}
END_EGEG
// EOF
