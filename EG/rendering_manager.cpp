// �쐬�� : ��
#include "rendering_manager.hpp"

#include "renderer_d3d11.hpp"

BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
RenderingManager::RenderingManager()
{
    renderer_ = RendererD3D11::create();
}
// �f�X�g���N�^
RenderingManager::~RenderingManager()
{
    delete renderer_;
}
END_EG_EG
// EOF
