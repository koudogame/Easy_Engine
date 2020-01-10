// �쐬�� : ��
#include "game.hpp"
#include "director.hpp"


BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// �Q�[���̎��s����
void Game::execute()
{
    // �Q�[���̏�����
    if( initialize() == false )
        return;

    // �Q�[�����[�v
    director_->getPlatform()->gameLoop( std::bind( &Game::update, this, std::placeholders::_1) );

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
    director_ = Director::instance();
    bool res = director_->initialize( PlatformID::kWindows );
    if( res == false ) return false;

    return true;
}

// �I������
//
// �Q�[���̏I�����ɕK�v�ȏ������L�q����
void Game::finalize()
{
    director_->getPlatform()->release();
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
    /*float back_color[4] { 1.0F, 0.0F, 0.0F, 1.0F };
    director_->getRenderer()->beginRender( back_color );

    director_->getRenderer()->endRender();*/

    return true;
}
END_EG_EG
// EOF
