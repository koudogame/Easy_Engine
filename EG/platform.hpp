#ifndef INCLUDED_EG_EG_PLATFORM_HEADER_
#define INCLUDED_EG_EG_PLATFORM_HEADER_
// �쐬�� : ��
#include <functional>
#include "easy_engine.hpp"
#include "renderer.hpp"

BEGIN_EG_EG
//
// �v���b�g�t�H�[���Ɉˑ�����@�\��񋟂���C���^�[�t�F�C�X
//
// ���������s���Ă��Ȃ��C���^�[�t�F�C�X����������邱�Ƃ�h�����߁A
// �C���X�^���X���𐧌����Ă��܂��B
// 
// ���̃C���^�[�t�F�C�X��PlatformFactory�ɂ���Đ�������܂��B
//
class IPlatform
{
public :
    virtual ~IPlatform() = default;

    //
    // �I������
    // ����O�ɕK�v�ȏ������������ĉ������B
    //
    virtual void finalize() = 0;

    //
    // �Q�[�����[�v
    // 
    // in pUpdatefunc : �����[�v�Ăяo���֐��̃|�C���^�B
    //
    // �����̊֐��|�C���^�́A�߂�l�� bool ����\��long long�^�̊֐��ւ̃|�C���^�ł��B
    // �n���ꂽ�֐��̖߂�l��false ���Ԃ��Ă����ꍇ�A���[�v���I�����܂��B
    // �n���ꂽ�֐��̈����ɂ́A�Ăяo�����̌o�ߎ���(: �~���b)��^���܂��B
    //
    virtual void gameLoop( std::function<bool(long long)> pUpdateFunc ) = 0;

    //
    // �_�C�A���O�{�b�N�X�̕\��
    //
    // in Message : �\�����镶����
    //
    virtual void showDialogBox( const char Message[] ) = 0;

protected :
    IPlatform() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_HEADER_
// EOF
