#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_

// �쐬�� : ��

#include "easy_engine.hpp"

BEGIN_EG_EG

//
// �Q�[���N���X ���@�V�[���̎��s��
//
class Game
{
public:
    //
    // �Q�[���̎��s
    //
    void execute();

private:
    bool initialize();
    void finalize();
    bool update(long long Erapsed);
};

END_EG_EG
#endif // INCLUDED_EG_EG_GAME_HEADER_
// EOF
