#ifndef INCLUDED_EG_EG_TEXTURE_HEADER_
#define INCLUDED_EG_EG_TEXTURE_HEADER_
// �쐬�� : ��
#include "easy_engine.hpp"
#include <memory>

BEGIN_EG_EG
//
// �e�N�X�`�����\�[�X�ւ̃C���^�[�t�F�C�X
// 
class ITexture
{
public :
    virtual ~ITexture() = default;

    // �e�N�X�`�����\�[�X�̉������
    virtual void release() = 0;
};
END_EG_EG
#endif // INCLUDED_EG_EG_TEXTURE_HEADER_
// EOF
