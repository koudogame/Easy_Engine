#ifndef INCLUDED_EG_EG_GAME_LOOP_HEADER_
#define INCLUDED_EG_EG_GAME_LOOP_HEADER_

// �쐬�� : ��

#include <functional>
#include "easy_engine.hpp"

BEGIN_EG_EG

//
// �Q�[�����[�v�N���X
//
// �Q�[�����[�v�ɍۂ��āA�v���b�g�t�H�[�����ɈقȂ�d�l���z������B
// �ÓI�ȃA�N�Z�X��񋟂���B
// �C���X�^���X�̐����͋֎~���Ă���B
//
class GameLoop
{
public :
    //
    // �Q�[�����[�v
    // 
    // in pFunction : �����[�v�Ăяo���֐��̃|�C���^�B
    //
    // �����̊֐��|�C���^�́A�߂�l�� bool ������long long�^�̊֐��B
    // �n���ꂽ�֐��̖߂�l��false ���Ԃ��Ă����ꍇ�A���[�v���I������B
    // �n���ꂽ�֐��̈����ɂ́A�Ăяo�����̌o�ߎ���(: �~���b)��^����B
    //
    static void loop( std::function<bool(long long)> pFunction );

private :
    GameLoop() = default;
};

END_EG_EG
#endif // INCLUDED_EG_EG_GAME_LOOP_HEADER_
// EOF
