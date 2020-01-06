#ifndef INCLUDED_EG_EG_INTERFACE_HEADER_
#define INCLUDED_EG_EG_INTERFACE_HEADER_
// �쐬�� : ��
#include "easy_engine.hpp"

BEGIN_EG_EG
//
// �C���^�[�t�F�C�X�p���N���X
//
class Interface
{
public :
    // �Q�Ɛ��J�E���g�A�b�v
    virtual void addRef() = 0;
    // ����@�Q�Ɛ���0�ɂȂ����玩�g�̃������̈��������邱��
    virtual void release() = 0;

protected :
    virtual ~Interface() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_INTERFACE_HEADER_
// EOF
