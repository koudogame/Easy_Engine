// �쐬�� : ��
#include "director.hpp"
#include "platform_factory.hpp"
//#include "renderer_factory.hpp"


BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
Director::Director()
{
    platform_ = PlatformFactory::instance()->create( PlatformID::kWindows );
}

// �f�X�g���N�^
Director::~Director()
{
    platform_->finalize();
    delete platform_;
}
END_EG_EG
// EOF
