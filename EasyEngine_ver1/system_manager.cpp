// �쐬�� : ��
#include "system_manager.hpp"

BEGIN_EGEG
SystemManager* SystemManager::instance_;

// SystemManager
/*===========================================================================*/
// �R���X�g���N�^
SystemManager::SystemManager( IPlatform* pPlatform ) :
    p_platform_( pPlatform )
{
}
// �f�X�g���N�^
SystemManager::~SystemManager()
{
    delete p_platform_;
}

// ���C�����[�v
void SystemManager::mainLoop( std::function<bool(uint64_t)> pFunc )
{
    p_platform_->mainLoop( pFunc );
}

// �_�C�A���O�{�b�N�X�̕\��
void SystemManager::showDialogBox( const std::string& Message )
{
    p_platform_->showDialogBox( Message );
}

// �C���X�^���X�̐���
void SystemManager::create( const EasyEngine& Creator, IPlatform* pPlatform )
{
    destroy( Creator );
    instance_ = new SystemManager( pPlatform );
}

// �C���X�^���X�̔j��
void SystemManager::destroy( const EasyEngine& Deleter )
{
    Deleter.proof();

    if( instance_ )
    {
        delete instance_;
        instance_ = nullptr;
    }
}
END_EGEG
// EOF
