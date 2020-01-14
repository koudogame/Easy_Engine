// �쐬�� : ��
#include "director.hpp"
#include "platform_factory.hpp"


BEGIN_EGEG
// �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
Director::Director()
{
}
// �f�X�g���N�^
Director::~Director()
{
    if( p_platform_ )
    {
        p_platform_->release();
    }
}

// ����������
bool Director::initialize( PlatformID Platform )
{
    if( PlatformFactory::instance()->create(Platform, &p_platform_) == false )
        return false;

    return true;
}
END_EGEG
// EOF
