// �쐬�� : ��
#include "message_receive_component.hpp"
#include "messenger.hpp"

BEGIN_EGEG
// MessageReceiveComponent : �֐��̎���
/*===========================================================================*/
// ������
bool MessageReceiveComponent::initialize()
{
    // ���b�Z���W���[�ɓo�^
    Messenger::instance()->registerReceiver( this );

    return true;
}
// �I��
void MessageReceiveComponent::finalize()
{
    // ���b�Z���W���[����o�^������
    Messenger::instance()->unregisterReceiver( this );
}
END_EGEG
// EOF
