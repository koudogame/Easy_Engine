// �쐬�� : ��

#include "game.hpp"
#include "game_loop.hpp"


BEGIN_EG_EG

// �֐��̎���
/*===========================================================================*/
// �Q�[���̎��s����
void Game::execute()
{
    // �Q�[���̏�����
    initialize();

    // �Q�[�����[�v
    GameLoop::loop( std::bind( &Game::update, this, std::placeholders::_1) );

    // �Q�[���̏I��
    finalize();
}

// ����������
//
// �Q�[���̏������ɕK�v�ȏ������L�q����B
//
// �������ɐ��������ꍇ�́@true
// �������Ɏ��s�����ꍇ��  false ��߂�l�Ƃ��ĕԋp���邱�ƁB
bool Game::initialize()
{


    return true;
}

// �I������
//
// �Q�[���̏I�����ɕK�v�ȏ������L�q����
void Game::finalize()
{

}

// �X�V����
//
// ���t���[���Ăяo�����B
// �����Ƃ��Ď󂯎�� ErapsedMS �͑O��Ăяo��������̌o�ߎ��Ԃ��i�[���Ă���B
// �o�ߎ��Ԃ̒P�ʂ̓~���b(: ms)�ł���B
//
// �X�V���p��(�Q�[�����p��)����ꍇ�́@true
// �X�V���I��(�Q�[�����I��)����ꍇ�́@false ��߂�l�Ƃ��ĕԋp���邱�ƁB
bool Game::update( long long ErapsedMS )
{
    return true;
}

END_EG_EG
// EOF
