// �쐬�� : ��
#include "scene_manager.hpp"
#include "system_manager.hpp"
#include "scene_factory.hpp"

BEGIN_EGEG
// SceneManager : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
SceneManager::SceneManager()
{
}
// �f�X�g���N�^
SceneManager::~SceneManager()
{
    
}

// �V�[���̒ǉ�
void SceneManager::push( uint32_t ID )
{
    // �V�[���̐�����������
    Scene* next = SceneFactory::instance()->create( ID );
    if( next == nullptr )
    {
        SystemManager::instance()->showDialogBox( 
            "�V�[���̐����Ɏ��s���܂����B\n"
            "ID�ɑΉ�����N���G�C�^�[���t�@�N�g���ɓo�^����Ă��܂���B\n"
            "\n�ꏊ : SceneManager::push"
        );
        return;
    }

    if( next->initialize() == false )
    {
        SystemManager::instance()->showDialogBox( 
            "�V�[���̏������Ɏ��s���܂����B\n"
            "\n�ꏊ : SceneManager::push"
        );
        return;
    }

    scenes_.push_back( next );
}

// �V�[���̍폜
void SceneManager::pop()
{
    // ��Ƀg�b�v�̃V�[���͕ێ����Ă���
    if( scenes_.size() <= 1U ) return;

    // �V�[���̃|�b�v
    Scene* poped = scenes_.back();
    scenes_.pop_back();
    poped->finalize();
    delete poped;
}

// �V�[���̓���ւ�
void SceneManager::swap( uint32_t ID )
{
    // �V�[���̐�����������
    Scene* next = SceneFactory::instance()->create( ID );
    if( next == nullptr )
    {
        SystemManager::instance()->showDialogBox(
            "�V�[���̐����Ɏ��s���܂����B\n"
            "ID�ɑΉ�����N���G�C�^�[���t�@�N�g���ɓo�^����Ă��܂���B\n"
            "\n�ꏊ : SceneManager::swap" 
        );
        return;
    }
    
    if( next->initialize() == false )
    {
        SystemManager::instance()->showDialogBox(
            "�V�[���̏������Ɏ��s���܂����B\n"
            "\n�ꏊ : SceneManager::swap"
        );
        return;
    }

    // ���݃A�N�e�B�u�ȃV�[�������
    scenes_.back()->finalize();
    delete scenes_.back();

    // �A�N�e�B�u�ȃV�[���̓���ւ�
    scenes_.pop_back();
    scenes_.push_back( next );
}

// �I������
void SceneManager::destroy()
{
    for (auto& scene : scenes_)
    {
        scene->finalize();
        delete scene;
    }
}
END_EGEG
// EOF
