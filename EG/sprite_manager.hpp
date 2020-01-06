#ifndef INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
// �쐬�� : ��
#include "sprite.hpp"

BEGIN_EG_EG
//
// �X�v���C�g�Ǘ���
// �X�v���C�g�̕`�����C�ɍs���A���\�[�X�̖��ʌ�����}������B
//
// �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
//
class SpriteManager
{
public :
    // �C���X�^���X�ւ̃A�N�Z�X
    static SpriteManager* instance() { static SpriteManager i; return &i; }

    //
    // Sprite�̕`����G���g���[
    //
    void entryRender( Sprite& Entry );

    //
    // �G���g���[����Ă���Sprite��`��
    //
    void render();
     
private :
    SpriteManager() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
// EOF
