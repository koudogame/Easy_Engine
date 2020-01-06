// �쐬�� : ��
#include "scene_manager.hpp"
#include "scene.hpp"
#include <shcore.h>

BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// �A�N�e�B�u�ȃV�[���̍X�V����
void SceneManager::update()
{
    // �O��̃t���[���ŏ��O���ꂽ�V�[�����������
    if( poped_scene_ )
    {
        poped_scene_->finalize();
        delete poped_scene_;
        poped_scene_ = nullptr;
    }


    getActive()->update();
}

// �A�N�e�B�u�ȃV�[���̕`�揈��
void SceneManager::draw()
{
    getActive()->draw();
}

// �V�[���̏��O����
// ���O��A�����ɃV�[�����������Ə������c���Ă���ꍇ�Ɋ댯�Ȃ̂ŁA
// ���O�Ώۂ̃V�[�����ꎞ�̈�Ɋi�[���Ă����B
void SceneManager::pop()
{
    poped_scene_ = scenes_.back();
    scenes_.pop_back();
}

// �V�[���̓���ւ�����
void SceneManager::swap( Scene* Next )
{
    pop();
    push( Next );
}
END_EG_EG
// EOF
