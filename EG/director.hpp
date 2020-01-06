#ifndef INCLUDED_EG_EG_DIRECTOR_HEADER_
#define INCLUDED_EG_EG_DIRECTOR_HEADER_
// �쐬�� : ��
#include "easy_engine.hpp"
#include "platform.hpp"
#include "renderer.hpp"

BEGIN_EG_EG
//
// �S�̓����N���X
// �V���O���g���N���X�ł��B�A�N�Z�X�ɂ� instance�֐����g�p���ĉ������B
//
class Director
{
public :
    ~Director();

    // �C���X�^���X�ւ̃A�h���X���擾���܂��B
    static Director* instance() { static Director i; return &i; }
    // �v���b�g�t�H�[���Ɉˑ�����@�\��񋟂���C���^�[�t�F�C�X���擾���܂��B
    IPlatform* getPlatform() const { return p_platform_; }
    // �`��@�\��񋟂���C���^�[�t�F�C�X���擾���܂��B
    IRenderer* getRenderer() const { return p_renderer_; }

    //
    // ����������
    // �K���ŏ��ɌĂяo���ĉ������B
    //
    // in Platform : �v���b�g�t�H�[��
    // in Renderer : �����_���[
    //
    // out true  : ����������
    // out false : ���������s
    //
    bool initialize( PlatformID Platform, RendererID Renderer );

    //
    // �I������
    // �K���Ō�ɌĂяo���ĉ������B
    //
    void finalize();
private :
    Director();

    IPlatform* p_platform_;
    IRenderer* p_renderer_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_DIRECTOR_HEADER_
// EOF
