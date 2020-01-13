// �쐬�� : ��
#include "game.hpp"
#include "core.hpp"


BEGIN_EGEG
// �֐��̎���
/*===========================================================================*/
// �Q�[���̎��s����
void Game::execute()
{
    // �Q�[���̏�����
    if( initialize() == false )
        return;

    // �Q�[�����[�v
    Core::instance()->getPlatform()->gameLoop( std::bind( &Game::update, this, std::placeholders::_1) );

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
    bool res = Core::instance()->initialize( Game::kTargetPlatform );
    if( res == false ) return false;

    return true;
}

// �I������
//
// �Q�[���̏I�����ɕK�v�ȏ������L�q����
void Game::finalize()
{
    Core::instance()->finalize();
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
    // �X�V����


    // �`�揈��

    return true;
}
END_EGEG
// EOF
