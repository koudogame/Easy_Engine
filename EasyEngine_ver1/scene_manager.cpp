// �쐬�� : ��
#include "scene_manager.hpp"
#include "system_manager.hpp"
#include "uid.hpp"

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
   /* Scene* next = 
        dynamic_cast<Scene*>(GameObjectFactory::instance()->create( ID ));
    if( next == nullptr )
    {
        SystemManager::instance()->showDialogBox( 
            "�V�[���̐����Ɏ��s���܂����B\n"
            "ID���V�[���̂��̂łȂ����A�V�[�����t�@�N�g���ɓo�^����Ă��܂���B"
        );
        return;
    }

    if( next->initialize() == false )
    {
        SystemManager::instance()->showDialogBox( "�V�[���̏������Ɏ��s���܂����B" );
        return;
    }
    next->setActive( true );

    scenes_.back()->setActive( false );
    scenes_.push_back( next );*/
}

// �V�[���̍폜
void SceneManager::pop()
{
    // ��Ƀg�b�v�̃V�[���͕ێ����Ă���
    if( scenes_.size() <= 1U ) return;

    // �V�[���̃|�b�v
    Scene* poped = scenes_.back();
    scenes_.pop_back();
    //poped->finalize();
    delete poped;
}

// �V�[���̓���ւ�
void SceneManager::swap( uint32_t ID )
{
    pop();
    push( ID );
}
END_EGEG
// EOF
