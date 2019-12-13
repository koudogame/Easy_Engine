// �쐬�� : ��
// �f�[�^�̈����� stack�Ȃ̂ɑ΂��A�R���e�i�� vector�Ȃ̂́A
// �g���o�[�X���\�ɂ��邽�߁B


#include "scene_manager.hpp"
#include "scene.hpp"

BEGIN_EG_EG

// �֐��̎���
/*===========================================================================*/
// �X�V����
void SceneManager::update()
{
    // �O��̍X�V�ŏ��O���ꂽ�V�[�����J��
    if( poped_scene_ )
    {
        poped_scene_->finalize();
        delete poped_scene_;
        poped_scene_ = nullptr;
    }

    for( auto& scene : scenes_ )
        scene->update();
}

// �`�揈��
void SceneManager::draw()
{
    for( auto& scene : scenes_ )
        scene->draw();
}

// �V�[���̓���ւ�����
void SceneManager::swap( Scene *Next )
{
    pop();
    push( Next );
}

// �V�[���̏��O����
// �����ɊJ������ƁA�������c���Ă���ꍇ�댯�Ȃ̂ŁA
// ��U�A�ꎞ�̈�ɓ����B
void SceneManager::pop()
{
    poped_scene_ = scenes_.back();
    scenes_.pop_back();
}

END_EG_EG
// EOF
