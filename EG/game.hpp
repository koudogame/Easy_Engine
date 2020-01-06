#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_
// �쐬�� : ��
#include "easy_engine.hpp"

BEGIN_EG_EG
class IPlatform;
class IRenderer;
//
// �Q�[���N���X ���@�V�[���̎��s��
// �Q�[���̒��j������ň����N���X�ł��B
// �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
//
class Game
{
public:
    static Game* instance() { static Game game; return &game; }

    //
    // �Q�[���̎��s
    //
    void execute();

private:
    Game() = default;

    bool initialize();
    void finalize();
    bool update(long long Erapsed);

    IPlatform* platform_ = nullptr;
    IRenderer* renderer_ = nullptr;
};
END_EG_EG
#endif // INCLUDED_EG_EG_GAME_HEADER_
// EOF
