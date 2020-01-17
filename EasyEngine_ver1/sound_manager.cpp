// �쐬�� : ��
#include "sound_manager.hpp"

BEGIN_EGEG
SoundManager* SoundManager::instance_;

// SoundManager
/*===========================================================================*/
// �R���X�g���N�^
SoundManager::SoundManager( ISoundLoader* pLoader ) :
    p_loader_( pLoader )
{
}
// �f�X�g���N�^
SoundManager::~SoundManager()
{
    delete p_loader_;
}

// �C���X�^���X�̐���
void SoundManager::create( const EasyEngine& Creator, ISoundLoader* pLoader )
{
    destroy( Creator );

    instance_ = new SoundManager( pLoader );
}
// �C���X�^���X�̔j��
void SoundManager::destroy( const EasyEngine& Deleter )
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
