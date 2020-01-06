#ifndef INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
// �쐬�� : ��
#include "renderer.hpp"

BEGIN_EG_EG
//
// �����_���[�̊Ǘ����s���B
// �V���O���g���N���X�ł��B�C���X�^���X�ւ̃A�N�Z�X�ɂ� instance�֐����g�p���ĉ������B
//
class RenderingManager
{
public :
    ~RenderingManager();

    static RenderingManager* instance() { static RenderingManager i; return &i; }

    IRenderer* getRenderer() const { return renderer_; }

private :
    RenderingManager();

    IRenderer* renderer_ = nullptr;
};
END_EG_EG
#endif // INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
// EOF
