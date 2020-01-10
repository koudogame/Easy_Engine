// �쐬�� : ��
#include "core.hpp"
#include "platform_factory.hpp"

BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// ����������
bool Core::initialize( PlatformID Platform )
{
    if( PlatformFactory::instance()->create(Platform, &p_platform_) == false )
        return false;

    return true;
}
// �I������
void Core::finalize()
{
    if( p_platform_ ) p_platform_->release();
}
END_EG_EG
// EOF
