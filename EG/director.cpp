// �쐬�� : ��
#include "director.hpp"
#include "platform_factory.hpp"
#include "renderer_factory.hpp"


BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
Director::Director()
{
}
// �f�X�g���N�^
Director::~Director()
{
}

// ����������
bool Director::initialize( PlatformID Platform, RendererID Renderer )
{
    if( PlatformFactory::instance()->create(Platform, &p_platform_) == false )
        return false;

    if( RendererFactory::instance()->create(Renderer, &p_renderer_) == false )
        return false;

    return true;
}

// �I������
void Director::finalize()
{
    if( p_renderer_ )
    {
        p_renderer_->release();
    }

    if( p_platform_ )
    {
        p_platform_->release();
    }
}
END_EG_EG
// EOF
